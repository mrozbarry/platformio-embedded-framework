#if defined(NATIVE_BUILD) && defined(DEBUG)
#include <iostream>
#endif

#include <OutputBuffer.hpp>

OutputBuffer::OutputBuffer(uint8_t width, uint8_t height)
  : width(width)
  , height(height)
  , isValid(width > 0 && height > 0)
  , buffer(NULL)
  , ownsBuffer(true)
{
  if (!isValid) {
    // should probably throw
    return;
  }
  buffer = new char*[height];
  for (uint8_t r = 0; r < height; r++) {
    buffer[r]  = new char[width];
  }
  clear();
}

OutputBuffer::OutputBuffer(OutputBuffer &other, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
  : width(width)
  , height(height)
  , isValid(width <= other.width && height <= other.height && x < (other.width - 1) && y < (other.height - 1))
  , buffer(NULL)
  , ownsBuffer(false)
{
  if (!isValid) {
    // should probably throw
    return;
  }
  buffer = new char*[height];
  for (uint8_t r = 0; r < height; r++) {
    buffer[r]  = other.offset(x, y + r);
  }
  clear();
}

OutputBuffer::~OutputBuffer()
{
  if (!buffer) return;
  if (ownsBuffer) {
    for(uint8_t r = 0; r < height; r++) {
      delete[] buffer[r];
      buffer[r] = NULL;
    }
  }
  delete[] buffer;
}

void OutputBuffer::clear()
{
  for(uint8_t y = 0; y < height; y++) {
    for(uint8_t x = 0; x < width; x++) {
      buffer[y][x] = ' ';
    }
  }
}

uint8_t OutputBuffer::print(uint8_t x, uint8_t y, const char *text)
{
  if (y >= height) return 0;

  uint8_t length = 0;
  for(uint8_t i = 0; i < width; i++) {
    if (x + i >= width) break;
    if (text[i] == 0) break;

    buffer[y][x + i] = text[i];
    length++;
  }

  return length;
}

char *OutputBuffer::offset(uint8_t x, uint8_t y)
{
  if (y >= height) return NULL;
  if (x >= width) return NULL;

  return (buffer[y] + x);
}

void OutputBuffer::debug()
{
#if defined(NATIVE_BUILD) && defined(DEBUG)
  std::cout << "OutputBuffer:" << std::endl;
  for(uint8_t r = 0; r < height; r++) {
    std::cout << '|';
    for(uint8_t c = 0; c < width; c++) {
      std::cout << (char)buffer[r][c];
    }
    std::cout << '|' << std::endl;
  }
  std::cout << "/--------" << std::endl;
#endif
}
