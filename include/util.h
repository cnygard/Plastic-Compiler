#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* read_ascii_file(const char* path);

bool isDigit(const char val);
bool isCharacter(const char val);
bool isPunctuation(const char val);