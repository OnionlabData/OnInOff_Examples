using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Runtime.InteropServices;
using UnityEngine;

public class Person : MonoBehaviour
{
 
    //MOV AQUI
    float Index; 
        
    bool used = false; 
   
    [Space(5)]
    [Tooltip("Tiempo antes de desactivar los objetos instanciados")]
    public float TimerNumber;
    private float InitialTimer;
    [Space(5)]
    [Tooltip("Para modificar la velocidad del objeto")]
    public float velocity = 5; 
    Rigidbody2D _rb;

    void Awake() 
    {
        _rb = GetComponent<Rigidbody2D>();
        used = true; 
        InitialTimer = TimerNumber;    
    }

    void Update()//Inicia un temporizador para detectar cuando ya no se utilitza más a esa persona.
    {       
       TimerNumber -= Time.deltaTime;        
        if (TimerNumber <= 0.0f) 
        {
         used = false;           
        }        
    }

    public void MoveToTarget(Vector3 _dir) //Recibie un vector de dirección y mueve a la persona a esa nueva posición. 
    {
        if (_rb != null)
        {
            _rb.MovePosition(Vector3.MoveTowards(transform.position, _dir, velocity));
        }
    }

    public void SetIndex(float index) //Modifica el indice de la persona al valor correspondiente.
    { 
        Index = index;        
    }
   
    public bool IsMyIndex(float index) //Para comprobar si el indice esta siendo usado o no.
    { 
           return Index == index; 
    }
    
    public bool Used()  //Para comporbar si la persona esta siendo usada o no.
    {
        return used;
    }
   
    public void UpdateXYZ(Vector3 Dir) //Recibe un vector de dirección, lo envia a la función de movimiento, marca a la persona como usada y por ultimo, reinicia el temporizador al valor marcado al principio.
    {       
        MoveToTarget(Dir);
        used = true;
        TimerNumber = InitialTimer;        
    }
  
    public void Remove() //Elimina a la persona de la escena.
    {      
        Destroy(gameObject);
    }
   
}
