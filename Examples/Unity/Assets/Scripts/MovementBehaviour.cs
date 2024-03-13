using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementBehaviour : MonoBehaviour
{
    [Space(5)]
    [Tooltip("indica la velocidad del objeto una vez que sea instanciado")]
    [SerializeField]
    public float velocity = 5; //Velocidad del objeto
    Rigidbody2D _rb;

    private void Start()
    {
        _rb = GetComponent<Rigidbody2D>();
    }

    public void MoveToTarget(Vector3 _dir) 
    {
        if (_rb != null)
        {           
            _rb.MovePosition(Vector3.MoveTowards(transform.position, _dir, velocity));     
        }      
    } 
}
