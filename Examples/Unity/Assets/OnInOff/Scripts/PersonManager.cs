using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Class PersonManager handles OSC input and manages current scene people.
/// </summary>
public class PersonManager : MonoBehaviour
{
    [Tooltip("OSC object necessary to receive person data")]
    public OSC Osc;
    [Tooltip("App target frames per second")]
    [SerializeField] private int _fps = 60;
    [Tooltip("App target frames per second")]
    [SerializeField] private Transform _personContainer;
    [Tooltip("Used to map coordinates. Sets top left corner of canvas")]
    [SerializeField] private Vector2 _topLeftCorner;
    [Tooltip("Used to map coordinates. Sets bottom right corner of canvas")]
    [SerializeField] private Vector2 _bottomRightCorner;
    [Tooltip("Add your prefab assigned to each person")]
    [SerializeField] private Person _personPrefab;
    private Dictionary<int, Person> _currentPeople = new Dictionary<int, Person>();

    // Adds destroy Person listener
    void Awake()
    {
        Application.targetFrameRate = _fps;
        Person.OnPersonNotUsed += OnPersonNotUsed;
    }

    // Initializes OSC listener
    // The /index address is defined by the OnInOff app
    void Start()
    {
        Osc.SetAddressHandler("/index", OnNewPersonCoord);
    }

    // Called every time OnInOff notifies a person coordinate
    private void OnNewPersonCoord(OscMessage message)
    {
        // Gets person index and normalized coordinates (between 0 and 1)
        int personIndex = message.GetInt(0);
        float xCoord = message.GetFloat(1);
        float yCoord = message.GetFloat(2);

        // Maps normalized coordinates to scene world coordinates
        float mappedXCoord = map(xCoord, 0, 1, _topLeftCorner.x, _bottomRightCorner.x);
        float mappedYCoord = map(yCoord, 0, 1, _topLeftCorner.y, _bottomRightCorner.y);
        Vector3 position = new Vector3(mappedXCoord, mappedYCoord, 0);

        //  If Person is already tracked, update position
        if (_currentPeople.ContainsKey(personIndex))
        {
            _currentPeople[personIndex].UpdatePosition(position);
        }
        // Otherwise create a new Person
        else
        {
            Person p = Instantiate(_personPrefab, position, Quaternion.identity, _personContainer);
            p.name = "Person_" + personIndex;
            p.Init(personIndex);
            p.UpdatePosition(position);
            // Add Person to dictionary to track it afterwards
            _currentPeople[personIndex] = p;
        }
    }

    // Called when a person notifies that it has not been updated in a while
    // Destroys Person object
    private void OnPersonNotUsed(int personIndex)
    {
        if (!_currentPeople.ContainsKey(personIndex)) return;
        Destroy(_currentPeople[personIndex].gameObject);
        _currentPeople.Remove(personIndex);
    }

    // Maps a value from ome arbitrary range to another arbitrary range
    private float map(float value, float leftMin, float leftMax, float rightMin, float rightMax)
    {
        if (leftMax - leftMin == 0) return 0;
        return rightMin + (value - leftMin) * (rightMax - rightMin) / (leftMax - leftMin);
    }
}