import openpyxl

# Open the Excel file
workbook = openpyxl.load_workbook('runtime.xlsx')
# Select the first sheet
sheet = workbook.active

try:
    # Read the contents of the runtime.txt file
    with open('runtime.txt', 'r') as file:
        lines = file.readlines()
except FileNotFoundError:
    print("File not found: runtime.txt")
    exit(1)
except:
    print("Error occurred while reading the file.")
    exit(1)

# Start from row 2
row_number = 3

# Iterate through the lines
for line in lines:
    # Remove leading and trailing whitespace
    line = line.strip()
    line = line.replace('.', ',')
    # Update the cell in the third column of the current row
    cell = sheet.cell(row=row_number, column=3)
    cell.value = line

    # Increment the row number
    row_number += 1

# Save the changes to the Excel file
try:
    workbook.save('runtime.xlsx')
except:
    print("Error occurred while saving the Excel file.")
    exit(1)

try:
    # Clean the runtime.txt file by overwriting with an empty string
    with open('runtime.txt', 'w') as file:
        file.write('')
except:
    print("Error occurred while cleaning the file.")
    exit(1)

print("File cleaned successfully.")
