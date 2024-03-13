using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Security.Cryptography.X509Certificates;
using UnityEngine;


public class OSC_Client : MonoBehaviour
{   

    [Space(5)]
    [Tooltip("Añadir GameObject con script de OSC Server")]
    public OSC osc; // Script de OSC.
   
    [Space(5)]
    [Tooltip("Añadir prefab del objeto que se desea instanciar, con script de MovementBehaviour, Person, complemento de RigidBody2D y complemento de Sprite Render")]
    public GameObject prefab; // Prefab del objeto, en el gameobject es necesario añadir script de MovementBehaviour, Person, complemento de RigidBody2D y complemento de Sprite Render.
   
    List<GameObject> GBList; // Lista de objetos instanciados.
   
    private GameObject aa; // Objeto instanciado.
   
    [Space(5)]
    [Tooltip("Tiempo antes de desactivar los objetos instanciados")]
    public float TimerNumber;// Float que se usa para indicar el tiempo antes de la destrucción del objeto.
   
    private float TimerNumber2;// Float que se usa para obligar a TimerNumber a que sea diferente a 0, hasta el momento de la destrucción.

    void Start() //Cuando se inicia, crea la lista de personas, y manda una señal para recibir mensajes OSC.
    {
        GBList = new List<GameObject>();

        osc.SetAddressHandler("/index", OnReceiveMSG);

        TimerNumber2 = TimerNumber;
    }
    void Update() // Esta funcion se utiliza de cronometro para indicar cuando ya no llegan mas mensajes de OSC.
    {
        TimerNumber -= Time.deltaTime;

            if(TimerNumber <=0.0f)
             {
               DestroyPerson(); //Invoca a la función DestroyPerson().
             }
    }
    void OnReceiveMSG(OscMessage message)
    {     
        float index = message.GetFloat(0); //Indice del objeto.
         
        float x = message.GetFloat(1); //Coordenada X del objeto.

        float y = message.GetFloat(2); //Coordenada Y del objeto.

        float z = message.GetFloat(3); //Coordenada Z del objeto.

        Vector3 dir = new Vector3(x * 100, y * -100, z * 0); // Se utiliza para crear un vector en 3d con las coordenadas recibidas.
        
        bool Exist = false;     

         for(int i=0;i<GBList.Count && !Exist ;i++) // Se utiliza para comprobar si el indice de la persona existe o no.
             {
                Exist = GBList[i].GetComponent<Person>().IsMyIndex(index);
             }

         if (!Exist) // En caso de no existir el indice, se crea una persona nueva con ese indice.
             {
                aa = Instantiate(prefab, dir, Quaternion.identity);

                aa.GetComponent<Person>().SetIndex(index);

                aa.name="Person " + index;           
            
                GBList.Add(aa);
             }

         for (int i = 0; i < GBList.Count; i++) // Se analiza toda la llista.
            {
                 if (GBList[i].GetComponent<Person>().IsMyIndex(index)) //Para cada indice, se le envia el Vector3 Dir que le corresponde. 
                     {
                        GBList[i].GetComponent<Person>().UpdateXYZ(dir);
                     }
                 if (false == GBList[i].GetComponent<Person>().Used()) //En caso de detectar que el mensaje OSC  no envia un indice.
                    {
                         GBList[i].GetComponent<Person>().Remove(); // Invoca a la función Remove() de la persona, para destruirla.

                         GBList.RemoveAt(i); //Se elimina de la lista el indice y la persona indicada.
                    }                   
        }
        TimerNumber = TimerNumber2;
    }
    void DestroyPerson() //Funcion que elimina a las personas, una vez que ya no se reciben mas mensajes OSC.
    {      
        for(int i = GBList.Count - 1; i >= 0; i--)
        {            
            if (false== GBList[i].GetComponent<Person>().Used())
            {              
                GBList[i].GetComponent<Person>().Remove(); // Invoca a la función Remove() de la persona, para destruirla.

                GBList.RemoveAt(i); //Se elimina de la lista el indice y la persona indicada.              
            }                                                                                
        }
    }
   }
  
 