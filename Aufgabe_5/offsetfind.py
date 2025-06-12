from pwn import *

context.binary = ELF('./tommysalami', checksec=False)
context.log_level = 'debug'

p = process('./tommysalami')
payload = cyclic(200)
p.sendline(payload)
p.wait()

core = p.corefile
print("RIP offset:", cyclic_find(core.read(core.rsp, 8)))

