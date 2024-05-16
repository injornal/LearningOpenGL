//
//  renderer.hpp
//  playground
//
//  Created by Kostiantyn Babich on 5/16/24.
//

#pragma once

#include <GL/glew.h>
#include <assert.h>

#define glCall(x) glClearError(); x; assert(glLogCall(#x))

void glClearError();

bool glLogCall(const char* function);

