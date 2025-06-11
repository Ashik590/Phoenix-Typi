# 🔥 Phoenix Typi – A Type Meter

**Phoenix Typi** is a terminal-based typing speed tracker built in **C** using the **ncurses** library.  
It gives you a fun and interactive way to improve your typing speed and accuracy — right from your terminal!

---

## ✨ Features

- 🖊️ **Typing Practice with Live Text Display**  
  Type the given sentence shown on the screen in real-time.

- 🎨 **Color-coded Feedback**  
  - ✅ Correct characters are shown in **green**  
  - ❌ Wrong characters are highlighted in **red**, with a caution alert for every mistake

- ⏱ **Custom Time Limits**  
  Choose your session duration:
  - 15 seconds
  - 30 seconds
  - 45 seconds
  - 60 seconds

- 🧠 **Difficulty Levels**  
  Select the level of complexity:
  - Easy  
  - Medium  
  - Hard  

- 💫 **Incredible Terminal UI**  
  - Eye-pleasing interface  
  - Smooth and stylish animations  
  - Built entirely with `ncurses` in C

- 📊 **Detailed Result Summary**  
  After finishing, you'll get a complete performance report:
  - 🚀 **WPM (Words Per Minute)**
  - ⌨️ **CPM (Characters Per Minute)**
  - 🎯 **Accuracy (%)**
  - ❌ **Wrong Characters Typed**
  - ❌ **Wrong Words Typed**
  - 🔢 **Total Characters Typed**
  - 🔠 **Total Words Typed**

---

## 🚀 How to Run

To run the application, open a terminal in the project directory and execute:

```bash
./app < word.txt
```

---

## 🛠️ How to Compile

If you want to compile the C source file yourself, ensure you have the following installed:
- GCC compiler
- Ncurses library

To compile, use:

```bash
gcc app.c -o app -lncurses
```

---

## 📄 License

[MIT](LICENSE)  
