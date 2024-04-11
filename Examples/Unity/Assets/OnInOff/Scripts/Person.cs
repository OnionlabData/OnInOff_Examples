using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Class Person handles person movement and person destruction behaviour.
/// </summary>
public class Person : MonoBehaviour
{
    public static Action<int> OnPersonNotUsed;
    [Tooltip("Time (in seconds) after the person has to be destroyed if it has not been updated")]
    [SerializeField] private float _timeout = 0.2f;
    private int _index;
    private float _lastTimeUpdated;

    void Awake() { }

    // Initializes person with it's corresponding index
    public void Init(int index)
    {
        _index = index;
    }

    // Checks if the object has been updated recently
    // If not, notifies PersonManager that it has to be destroyed
    void Update()
    {
        if (Time.time - _lastTimeUpdated > _timeout)
        {
            OnPersonNotUsed?.Invoke(_index);
        }
    }

    // Updates object position and last updated time
    public void UpdatePosition(Vector3 newPosition)
    {
        _lastTimeUpdated = Time.time;
        transform.position = newPosition;
    }
}
