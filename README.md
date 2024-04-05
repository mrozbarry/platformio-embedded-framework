# Arduino + I2C LCD Framework

Developed for Ardunio Nano (ATmega328P) with an LCD screen

## Setup

 1. `brew install platformio`
 2. `pio run -e development` will build and run the native build in your terminal
 3. To run the native build, the executable is `./.pio/build/development/program`

## Documentation

### `lib/vendor`

The `lib/vendor` folder is the framework for building applications.
The main goal is `lib/vendor` is to provide base classes and a foundation for building applications, specifically targetting applications displayed on constrained text-only LCD screens.

#### `class Message`

`Message`s are objects with types that can pass data around to different objects in the application.
Any `Message` usually looks like `Message(Message::Type::THING)`, and this message will be passed to every object in the application.
Using the `type` property, any object can determine if it needs to cast the Message to a child-class.

#### `class Lifecycle`

Arduino C applications have two main functions, `init` and `loop`.
Lifecycle has parallel virtual methods, `init(unsigned long now)` and `tick(unsigned long now)`.
`init` is meant to be called when the C method `init` is called, *OR* when a new object is dynamically created during program execution.
`tick` is called on each successive C `loop`.
In both cases, `init` and `tick` receive the current timestamp from Arduino's `millis()` implementation, which is meant to give each `Lifecycle`-derived object a consistent way of updating.

A `Lifecycle` object can also implement `message(Message *)`, which is a way to receive messages passed through the application.
Typically the `message` method will consist of a `switch(message->type)` and will determine which message types are important for the current object, or which messages can be ignored.

#### `class Application`

The application is a special singleton `Lifecycle` object that should track which objects are being used by the application, as well as triggering their `init`, `tick`, and `message` methods.
Applications can also `queue(Message*)` which will send a given `Message*` to all the registered `Lifecycle` objects.

### `src`


## Future work

### Components

I would like to have an interface in pages that could behave like this:

```
Page::Render *render()
{
  return new Columns([
    new Text("Hello"),
    new Text("World", Text::Align::Right),
  ], 2);
}
```

Which could render something like:

```
+----------------+
|Hello      World|
|                |
+----------------+
```
