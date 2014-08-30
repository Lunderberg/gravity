# -*- python -*-

import os

env = Environment(env=os.environ)
env.Append(CPPFLAGS=['-std=c++11'])
env.Append(CPPPATH=['include'])

env.Program(['main.cc',Glob('src/*.cc')])
