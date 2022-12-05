# Arduino + I2C LCD Framework

Developed for Ardunio Nano (ATmega328P) with an LCD screen

## Setup

 1. `brew install platformio`
 2. `pio run -e development` will build and run the native build in your terminal
 3. To run the native build, the executable is `./.pio/build/development/program`

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
