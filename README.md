# xv6_6.S081
Just for fun :P
* How to debug

In one terminal:

```shell
make qemu-gdb

# You will get tcp::[Some Number]
```

In another terminal:

```shell
riscv64-unknown-elf-gdb # sometimes use 'gdb'

...

(gdb) target remote localhost:[Some Number]
```


