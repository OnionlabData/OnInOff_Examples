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
    public OSC Osc; 
    [Space(5)]
    [Tooltip("Añadir prefab del objeto que se desea instanciar, con script de MovementBehaviour, Person, complemento de RigidBody2D y complemento de Sprite Render")]
    public Person Prefab;
    List<Person> PersonList;
    [Space(5)]
    [Tooltip("Tiempo antes de desactivar los objetos instanciados")]
    public float TimerNumber;
    private float InitialTimer;
    [Space(5)]
    [Tooltip("Para modificar la escala con valor X")]
    public float ScaleFactorX;
    [Space(5)]
    [Tooltip("Para modificar la escala con valor Y")]
    public float ScaleFactorY;

    void Awake() //Limita el framerate a 60 fps/s.
    {
        Application.targetFrameRate = 60;
    }

    void Start() //Inicia el protocolo de recibida de OSC.
    {
        PersonList = new List<Person>();

        Osc.SetAddressHandler("/index", OnReceiveMSG);

        InitialTimer = TimerNumber;
    }

    void Update() //Inicia un temporizador para detectar cuando ya no se recibe mas mensajes de tipo OSC.
    {
        TimerNumber -= Time.deltaTime;

        if (TimerNumber <= 0.0f)
        {
            //Cuando el temporizador llega a 0, inicia un protocolo para eliminar las personas creadas.
            DestroyAll(); 
        }
    }
    void OnReceiveMSG(OscMessage message) //Inicia un protocolo para la recepción de mensajes OSC.
    {
        float index = message.GetFloat(0); 

        float x = message.GetFloat(1);

        float y = message.GetFloat(2);

        float z = message.GetFloat(3); 

        Vector3 dir = new Vector3(x * ScaleFactorX, y * -ScaleFactorY, z * 0); 

        bool Exist = false;

        for (int i = 0; i < PersonList.Count && !Exist; i++) //Analiza la lista para determinar si una persona existe o no.
        {
            Exist = PersonList[i].IsMyIndex(index);
        }

        if (!Exist) //En caso de no existir, se crea una persona con el indice que sea necesario.
        {
            Person aa = Instantiate(Prefab, dir, Quaternion.identity, transform);

            aa.SetIndex(index);

            aa.name = "Person " + index;

            PersonList.Add(aa);
        }

        for (int i = 0; i < PersonList.Count; i++) //Para cada indice, se le envia sus nuevas coordenadas XYZ.
        {
            if (PersonList[i].IsMyIndex(index))  
            {
                PersonList[i].UpdateXYZ(dir);
            }
            DestroyPersonNotUsed(i); //En caso de detectar que es un indice no usado, se procede a su elíminación.
        }
        TimerNumber = InitialTimer; //Resetea el temporizador a su valor por defecto.
    }

    void DestroyAll()
    {
        for (int i = PersonList.Count - 1; i >= 0; i--)
        {
            DestroyPersonNotUsed(i);
        }
    }

    void DestroyPersonNotUsed(int i) //Cuando se le envia un indice, destruye a esa persona.
    {

        if (false == PersonList[i].Used())
        {
            PersonList[i].Remove();

            PersonList.RemoveAt(i);

        }
    }
}

