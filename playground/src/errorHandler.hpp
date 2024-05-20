//
//  errorHandler.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/19/24.
//

#pragma once

#include <GL/glew.h>
#include <assert.h>

#define glCall(x) glClearError(); x; assert(glLogCall(#x))

void glClearError();

bool glLogCall(const char* function);

