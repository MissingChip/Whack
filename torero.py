#!/bin/python3

import sys
import subprocess
import os
import re
from typing import List, Set, Dict, Tuple, Optional, Union
from os.path import *

def get_includes(filename: str):
    file = open(filename, 'r')
    includes = []
    noinclude = 0
    try:
        for line in file.readlines():
            if line.strip().startswith("#include"):
                s = re.search(".*\"(.+)\"", line)
                if s:
                    includes.append(s.group(1))
                    continue
                s = re.search(".*<(.+)>", line)
                if s:
                    includes.append(s.group(1))
                    continue
                #print("bad include line: {}".format(line))
    except UnicodeDecodeError:
        print("Unicode decode error in:", filename)
    except:
        print("Unexpected error:", sys.exc_info()[0])
        raise
    return includes

class Dir:
    search_ignore = []
    def __init__(self, dir:str = "./", ignore:Union[List[str], Tuple[str], str] = None):
        self.set_ignore(ignore)
        self.name = dir
        self.files = []
        self.dirs = []
        l = os.listdir(dir)
        for o in l:
            if (o not in self.search_ignore) and (os.path.realpath(o) not in self.search_ignore):
                if os.path.isfile(os.path.join(dir, o)):
                    self.files.append(o)
                elif os.path.isdir(os.path.join(dir, o)):
                    self.dirs.append(Dir(os.path.join(dir, o)))
    
    def search_ext(self, end):
        out = []
        for f in self.files:
            if f.endswith(end):
                out.append(os.path.join(self.name, f))
        for d in self.dirs:
            s = d.search_ext(end)
            if s:
                out.extend(s)
        return out

    def search_file(self, name: str):
        p = os.path.join(self.name, name)
        if os.path.isfile(p):
            return os.path.normpath(p)
        for f in self.files:
            if f == name:
                return os.path.join(self.name, f)
        for d in self.dirs:
            s = d.search_file(name)
            if s:
                return s
        return None
    
    def search_file_list(self, names: List[str]):
        found = []
        for name in names:
            s = self.search_file(name)
            if s:
                found.append(s)
        return found
    
    def set_ignore(self, ignore):
        if ignore != None:
            if isinstance(ignore, str):
                if os.path.exists(ignore):
                    self.search_ignore = [os.path.realpath(ignore)]
                else:
                    self.search_ignore = [ignore]
            else:
                self.search_ignore = []
                for f in ignore:
                    if os.path.exists(f):
                        self.search_ignore.append(os.path.realpath(f))
                    else:
                        self.search_ignore.append(f)


class CTarget:
    all_targets = {}
    dir = None
    def __init__(self, file_name, file_path = None, dir = './',ignore = None, targets_used = [], flags = ""):
        if not self.dir:
            self.dir = Dir(dir, ignore)
        self.parent, self.name = os.path.split(file_name)
        if file_path:
            self.path = file_path
        else:
            self.path = self.dir.search_file(file_name)
        self.targets = []
        self.flags = flags
        self.all_targets[self.name] = self
        includes = get_includes(self.path)
        if includes:
            for f in includes:
                s = self.dir.search_file(f)
                if f not in targets_used and s:
                    t = targets_used.copy()
                    t.append(f)
                    self.targets.append(CTarget(f, s, targets_used = t))

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        if self.targets:
            if len(self.targets) == 1:
                return "{} -> {}".format(self.name, self.targets[0])
            return "{} -> {}".format(self.name, self.targets)
        return self.name
    
    def recent(self):
        if self.targets:
            return max(os.path.getmtime(self.path), max([t.recent() for t in self.targets]))
        return os.path.getmtime(self.path)
    
    def include_dirs(self):
        dirs = [os.path.split(self.path)[0]]
        for t in self.targets:
            a = t.include_dirs()
            if a:
                dirs.extend([b for b in a if b not in dirs])
        return dirs

#potentially should use os.name, not sure what the compiling situation is on other platforms
default_compiler = ""
flag = {}
if os.name == 'posix':
    default_compiler = 'g++'
    flag = {
        "o": "-o {}",
        "L": "-L{}",
        "I": "-I{}",
        "l": "-l{}",
        "c": "-c"
    }
else:
    default_compiler = 'cl'


class Piler:
    exit_on_fail = 0
    def __init__(self, dir = "./", ignore = ("./include", "obj", "lib"), compiler = default_compiler, flags = "", lib_dir = "./lib", obj_dir = "./obj", out_dir = "./",libs = []):
        CTarget.dir = Dir(dir = dir, ignore = ignore)
        self.compiler = compiler
        self.sources = CTarget.dir.search_ext((".c", ".cpp"))
        self.targets = [CTarget(s) for s in self.sources]
        self.lib_dir = lib_dir
        self.obj_dir = obj_dir
        self.flags = flags
        self.libs = libs
    
    def run(self):
        for target in self.targets:
            if not os.path.exists(self.lib_dir):
                os.makedirs(self.lib_dir)
            if not os.path.exists(self.obj_dir):
                os.makedirs(self.obj_dir)
            self.make(target)

    def make_main(self, flags: str = "", name="a.out"):
        s = "{} {} {} {} {}".format(self.compiler, flag["o"].format(name),self.obj_dir+"/*", self.flags, flags)
        print(s)
        os.system(s)

    def make(self, target: CTarget):
        recent = 0
        trecent = target.recent()
        output, ext = os.path.splitext(target.name)
        o = output + ".o"
        output = normpath(join(self.obj_dir, o))
        if os.path.exists(output):
            recent = os.path.getmtime(output)
        else:
            print(output, "not found")
        if trecent > recent:
            print(trecent, recent)
            self.compile(target, output)
            self.package(o)

    def package(self, output):
        print(">]", output)

    def compile(self, target: CTarget, output: str):
        sys_str = "{} {} {} {}".format(self.compiler, target.path, flag['c'], flag['o'].format(output))
        inc = target.include_dirs()
        for i in inc:
            if i:
                sys_str += " "+flag["I"].format(i)+" "+target.flags+" "+self.flags
        print(sys_str)
        if os.system(sys_str) and self.exit_on_fail:
            raise Exception("Failure on {}".format(target.name))

if __name__ == "__main__":
    c = Piler(flags="-Iinclude/freetype -Iinclude/freetype/include")
    c.run()
    c.make_main("-lGL -lGLEW -lglfw -lfreetype -Iinclude", name="visual")
    #print(c.sources)
