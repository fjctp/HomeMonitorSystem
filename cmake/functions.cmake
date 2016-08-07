cmake_minimum_required(VERSION 2.8)

function(convert2number input_variable)
  if(${input_variable})
    set(${input_variable} 1 PARENT_SCOPE)
  else()
    set(${input_variable} 0 PARENT_SCOPE)
  endif()
endfunction(convert2number)