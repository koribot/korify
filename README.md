# Korify 🗜️


It is still Under 🚧 🛠️

- This is me trying to explore C, the concept of pointers, and the like. The encryption "algorithm" is not good (it's actually bad) and needs a lot of work.

- 👇 What is Korify 👇
```
korify is a  CLI tool designed for encrypting and decrypting plain text files of various formats, including:

📄 .txt
💻 .c
🔧 .cpp
🌐 .js
...and more!

🔒 Encrypt Files: Secure your files by encrypting them with a custom encryption key/string.
🔓 Decrypt Files: Decrypt your files using the same encryption key/string.
❗  Warning: Decrypting a file with the wrong key will still produce an output, but the content will differ from the original.

```

## Usage
- You need to install C compiler, (gcc, llvm)
- Compile the program
    ```
    gcc -Iheaders -o kori main.c lib/*.c
    ```
    - Alternatively you can download the pre-combiled version                 https://github.com/koribot/korify/releases/tag/v0.0.0 
      , after donwloading it you cant open it directly as it will close immediately, you can run  it by opening cmd in current directory where the pre-combiled version is downloaded and run:
      ```
        kori.exe "choose your command"
      ```
- Run the program
 
    - Encrypt file
    ```
     ./kori -ef "path to your source file" "path to your encrypted output file"
    ```
    ```
    $ ./kori -ef  main_encrypted.txt main_decrypted.txt
        ------------------------------
        | File successfully loaded |
        ------------------------------
        
        Enter your encryption string: korify
        ------------------------------
        | ** Encryption successful ** |
        ------------------------------
        --------------------------------------------
        | Encrypted output file ->: main_decrypted.txt |
        --------------------------------------------
    ```
    - Decrypt file -> (You can try to decrypt `main_encrypted.txt` with decryption string: walid)
    ```
     ./kori -df "path to your encrypted source file" "path to your decrypted output file"
    ```
    ```
    $ kori -df main_encrypted.txt main_decrypted.txt
        ------------------------------
        | File successfully loaded |
        ------------------------------
        
        Enter decrypting string: korify
        
        ---------------------------
        | Successfully Decrypted |
        ---------------------------
    ```
    - Even if you provide wrong decryption key it will still print "Successfully Decrypted",
      but the output file will not be the same as the original file
    


## Commands
- `-ef`👉 short for encrypt file
   - `./kori -ef sample.txt encrypted.txt`
   - ./kori -ef sample.txt  -> get the sample.txt on the current directory
   
- `-df`👉 short for decrypt file
   - `./kori -df encrypted.txt decrypted.txt`

- `-h` or `help`👉 prints help options
   - `./kori -h` or `./kori -help`

- `-v` or `version`👉 prints current version of korify
   - `./kori -v` or `./kori -version`



## Todos
- [ ] make a better way of checking valid path
- [ ] improve encrypting logic - maybe provide a list of encryption "technique" to users
- [ ] make it cross platform
- [ ] use UTF-8 encoding instead of ASC II 
