# CyclicExecutionState

CyclicExecutionState is a QState wrapper to execute functions cyclically while the state is active. The functions used can be static or bound to an object to use its own parameters and functions.

## Constructor
````CyclicExecutionState(QString name, int period_ms, const std::function<void()>& function);````

where:
- name is the name of the state
- period_ms is the period of execution of the function associated with the state.
- function is the function that will be executed cyclically within the state, it shall return void and have no parameters.

## Example of construction with a static function
Will cyclically execute the function, but will have no communication with the "outside".

```CyclicExecutionState *s1 = new CyclicExecutionState("Name State", 500, &function);```

## Example of construction inside an object
Will cyclically execute the object's function, and will have all parameters and functions of the object

```CyclicExecutionState *s1 = new CyclicExecutionState("Name State", 500, std::bind(&Object::function, this));```
    

    
