/*
ONINOFF PROCESSING EXAMPLE
01/03/2024
*/

// Before trying the sketch, you should import the library OSCP5 (From menu /Sketch/Import Library/Manage libraries...)
import oscP5.*;
import netP5.*;
// -----

import java.util.*; 
import java.util.stream.*; 

final int LISTENING_PORT = 12000;
final String PERSON_PATTERN = "/index"; // OSC person pattern
final int ALIVE_AFTER_UPDATED_MS = 500; // Time to remove a person after the last position input was received. In millis.

// Osc object
OscP5 oscP5;

// Person tracker
PersonManager personManager = new PersonManager();

void setup() {
  size(800, 600);
  frameRate(30);
  // Creates OSC listener
  oscP5 = new OscP5(this, LISTENING_PORT);
}

void draw() {
  background(0); 
  // Updates person tracker
  personManager.updateAndDraw();
}

// Manages OSC inputs
void oscEvent(OscMessage theOscMessage) {
  // Check if theOscMessage has the Oninoff person address pattern
  if(theOscMessage.checkAddrPattern(PERSON_PATTERN)==true) {
    // Check if the typetag is the right one: person_index (int) x_pos (float) y_pos (float)
    if(theOscMessage.checkTypetag("iff")) {
      // Parse theOscMessage and extract the values from the osc message arguments
      int personId = theOscMessage.get(0).intValue();  
      float personX = theOscMessage.get(1).floatValue();
      float personY = theOscMessage.get(2).floatValue();
      // Try to add person to manager
      personManager.addOrUpdate(personId, new PVector(personX, personY));
      // Feedback
      //println("Received an osc message /index with id: " + personId);
      return;
    }  
  } 
}

// Class that manages all the person objects
class PersonManager{
  
  // Holds current person objects
  ArrayList<Person> people = new ArrayList<Person>();
  
  PersonManager(){}
  
  // Checks if a new OSC input has to be assigned to an existing person or create one
  void addOrUpdate(int id, PVector normalizedPos){
    synchronized(this){
      // Get all the current person ids
      List<Integer> peopleIds = people.stream().map(p -> p.getId()).collect(Collectors.toList());
      PVector pos = new PVector(normalizedPos.x * width, normalizedPos.y * height);
      // If the OSC id is tracked, just update it
      if(peopleIds.contains(id)){
        int personIndex = peopleIds.indexOf(id);
        people.get(personIndex).updatePos(pos);
      }
      // Otherwise create a new person with the new data
      else{
        people.add(new Person(id, pos));
      }
    }
  }
  
  // Updates every person
  void updateAndDraw(){
    synchronized(this){
      for(int i = people.size() - 1; i >= 0; i--){
        Person currPerson = people.get(i);
        // If a person id has not been received in a while, remove person
        if(!currPerson.updateAndDraw()) people.remove(i);
      }
    }
  }
}

// Class for a tracked person
class Person{
  
  int id;
  PVector pos;
  long lastTimeUpdated;
  
  Person(int id, PVector pos){
    this.id = id;
    this.pos = pos;
    updated();
  }
  
  int getId(){
    return id;
  }
  
  // Records the last time the person position was updated
  void updated(){
    lastTimeUpdated = millis();
  }
  
  // Updates person current position
  void updatePos(PVector newPos){
    pos = newPos;
    updated();
  }
  
  // Checks if person has to be destroyed and paints it
  boolean updateAndDraw(){
    if(millis() - lastTimeUpdated > ALIVE_AFTER_UPDATED_MS) return false;
    paint();
    return true;
  }
  
  // Draw method
  void paint(){
    pushStyle();
    fill(255);
    ellipse(pos.x, pos.y, 30, 30);
    textSize(14);
    textAlign(CENTER, CENTER);
    text(id, pos.x, pos.y + 25);
    popStyle();
  }
  
}
