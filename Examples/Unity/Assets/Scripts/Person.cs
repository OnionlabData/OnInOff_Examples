using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Runtime.InteropServices;
using UnityEngine;

public class Person : MonoBehaviour
{

    float Index; // Indice que se le otorga al objeto una vez instanciado.
    
    MovementBehaviour mv; // Script de movimiento del objeto.
    
    public bool used = false; //Bool que se utiliza para comprobar que se utiliza el indice.
   
    [Space(5)]
    [Tooltip("Tiempo antes de desactivar los objetos instanciados")]
    public float TimerNumber;// Float que se usa para indicar el tiempo antes de la destrucción del objeto.
    
    private float TimerNumber2;// Float que se usa para obligar a TimerNumber a que sea diferente a 0, hasta el momento de la destrucción.

    void Awake()
    {
        mv = GetComponent<MovementBehaviour>(); //Inicializar el componente de movimiento.
       
        TimerNumber2 = TimerNumber;     // Se obliga a TimerNumber2 ha tener el mismo numero que TimerNumber.
    }
    void Start()
    { 
        used = true; //Una vez instanciado el objeto, se pone a TRUE el booleano para indicar que existe.
    }
    void Update() // Esta funcion se utiliza de cronometro para indicar cuando hay que destruir el objeto. 
    {       
       TimerNumber -= Time.deltaTime;
        
        if (TimerNumber <= 0.0f) //Una vez que TimberNumber llega a 0, se le cambia su booleano a FALSE.
        {
         used = false;           
        }

    }
    public void SetIndex(float index) //Funcion que pone el Indice que recibe desde OSC_Client al indice de la persona.
    { 
        Index = index;        
    }
   
    public bool IsMyIndex(float index) //Para comprobar que el indice que le llega es el mismo que el suyo. En caso que sea, se envia un TRUE. En caso contrario, se envia un FALSE.
    { 
           return Index == index; 
    }
    
    public bool Used() //Para comprobar que valor tiene used.
    {
        return used;
    }
   
    public void UpdateXYZ(Vector3 Dir) //Para indicar los nuevos valores de las coordenadas de X,Y,Z que tiene la persona.
    {       
        mv.MoveToTarget(Dir);
        used = true;
        TimerNumber = TimerNumber2;    
    }
  
    public void Remove() // Funcion para destruir el objeto.
    {      
        Destroy(gameObject);
    }
   
}
