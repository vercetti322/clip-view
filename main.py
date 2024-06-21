from tkinter import *
from tkinter import ttk
from tkinter import font

# Initialize the Tkinter application
root = Tk()
root.title('View Clipboard')
root.geometry('600x150')

# Create the mainframe with padding
mainframe = ttk.Frame(root, padding='15')
mainframe.pack(expand=True, fill='both')  # Pack mainframe to fill root window

# make custom font
custom_font = font.Font(family='Roboto', size=14)

# Create the Text widget for clipboard content
text_widget = Text(mainframe, padx=5, pady=5, font=custom_font, wrap='word')
text_widget.pack(expand=True, fill='both')  # Pack text widget to fill mainframe

# make Scroll Bar
scrollbar = ttk.Scrollbar(mainframe, orient='vertical', command=text_widget.yview)
scrollbar.pack(side='right', fill='y')

# config the text widget for this
text_widget.config(yscrollcommand=scrollbar.set)

# Insert dummy text into the Text widget
text_widget.insert('1.0', 'Our independent, member-supported model means we don’t sell your attention (or data) to advertisers. Our focus is on connecting you to stories that matter. \
Our independent, member-supported model means we don’t sell your attention (or data) to advertisers. Our focus is on connecting you to stories that matter. \
Our independent, member-supported model means we don’t sell your attention (or data) to advertisers. Our focus is on connecting you to stories that matter.')

# make the text read-only
text_widget.config(state='disabled')

# Start the Tkinter event loop
root.mainloop()
