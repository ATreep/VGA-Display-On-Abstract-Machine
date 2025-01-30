import lldb
import os

def on_exit(debugger, command, result, dict):
    debugger.HandleCommand('process kill')

def connect_remote(debugger, command, result, dict):
    am_home = os.environ.get('AM_HOME')
    if not am_home:
        print("AM_HOME environment variable is not set.")
        return
    
    path = f'{am_home}/am/src/x86/qemu/boot/boot.o'
    debugger.HandleCommand(f'target create {path}')
    debugger.HandleCommand('gdb-remote 1234')
    debugger.HandleCommand('breakpoint set -name _start')
    debugger.HandleCommand('breakpoint set -name start32')
    debugger.HandleCommand('process continue')

# Ensure script runs automatically when imported
def __lldb_init_module(debugger, dict):
    debugger.HandleCommand('command script add -f debug.on_exit on_exit')
    connect_remote(debugger, None, None, None)