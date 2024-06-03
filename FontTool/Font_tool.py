import tkinter as tk
import re

class BitmapEditor:
    def __init__(self, master, filename):
        self.master = master
        self.filename = filename
        self.canvas = tk.Canvas(master, width=400, height=400, bg='white')
        self.canvas.pack()
        self.cells = [[0 for _ in range(16)] for _ in range(16)]
        self.rects = [[None for _ in range(16)] for _ in range(16)]
        self.cell_size = 25
        self.create_grid()
        self.canvas.bind("<Button-1>", self.toggle_cell)
        self.export_button = tk.Button(master, text="Save", command=self.export)
        self.export_button.pack()
        self.clear_button = tk.Button(master, text="Clear", command=self.clear)
        self.clear_button.pack()
        self.current_char = 'a'
        self.prompt_label = tk.Label(master, text=f"Draw: {self.current_char}")
        self.prompt_label.pack()
        self.load_char()

    def create_grid(self):
        for i in range(16):
            for j in range(16):
                x1 = i * self.cell_size
                y1 = j * self.cell_size
                x2 = x1 + self.cell_size
                y2 = y1 + self.cell_size
                self.rects[i][j] = self.canvas.create_rectangle(x1, y1, x2, y2, fill='white')

    def toggle_cell(self, event):
        i = event.x // self.cell_size
        j = event.y // self.cell_size
        self.cells[i][j] = 1 - self.cells[i][j]
        color = 'black' if self.cells[i][j] else 'white'
        self.canvas.itemconfig(self.rects[i][j], fill=color)

    def export(self):
        with open(self.filename+"new.txt", 'a') as f:
            f.write(f"const uint8_t number_{self.current_char}_16[16] = {{")
            for j in range(16):
                val = sum(1 << i for i in range(16) if self.cells[i][j])
                f.write(f"0x{val:02X}")
                if j < 15:
                    f.write(", ")
            f.write("};\n")
        self.next_char()
        self.load_char()

    def clear(self):
        for i in range(16):
            for j in range(16):
                self.cells[i][j] = 0
                self.canvas.itemconfig(self.rects[i][j], fill='white')

    def next_char(self):
        if self.current_char == 'z':
            self.current_char = '0'
        elif self.current_char == '9':
            self.current_char = 'a'
        else:
            self.current_char = chr(ord(self.current_char) + 1)
        self.prompt_label.config(text=f"Draw: {self.current_char}")

    def load_char(self):
        self.clear()
        with open(self.filename, 'r') as f:
            for line in f:
                match = re.match(r'const uint8_t number_(.)_16\[16\] = {([^}]+)};', line)
                if match and match.group(1) == self.current_char:
                    values = list(map(lambda x: int(x, 16), match.group(2).split(', ')))
                    for j in range(16):
                        for i in range(16):
                            self.cells[i][j] = (values[j] >> i) & 1
                            color = 'black' if self.cells[i][j] else 'white'
                            self.canvas.itemconfig(self.rects[i][j], fill=color)
                    break

root = tk.Tk()
 
editor = BitmapEditor(root, 'C:\\Users\\james\\Desktop\\Newfolder\\bit.txt')
root.mainloop()
