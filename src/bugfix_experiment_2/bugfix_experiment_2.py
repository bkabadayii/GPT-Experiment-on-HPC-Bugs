import openai
import os
import subprocess
import time
from dotenv import load_dotenv

def execute_cpp_files_recursive(folder_path, output_file):
    with open(output_file, 'w') as file:
        for root, dirs, files in os.walk(folder_path):
            for file_name in files:
                if file_name.endswith(".cpp"):
                    file_path = os.path.join(root, file_name)
                    execute_cpp_file(file_path)

def execute_cpp_file(file_path, flags=None):
    # Compile the C++ file with optional flags, including -fopenmp
    compile_command = ["g++", file_path, "-o", "output", "-fopenmp"]
    if flags:
        compile_command.extend(flags)
    compile_process = subprocess.run(compile_command, text=True)
    if compile_process.returncode != 0:
        print(f"Compilation error for file '{file_path}': {compile_process.stderr}")
        return

    # Execute the compiled program
    execution_process = subprocess.run(["./output"], text=True)
    if execution_process.returncode != 0:
        print(f"Execution error for file '{file_path}': {execution_process.stderr}")
        return



problematicCodeArr = []

def print_2d_array(arr):
    for row in arr:
        for element in row:
            print(element, end=" ")
        print()

def remove_prefix_suffix(string):
    prefix = "problematic/"
    suffix = "/problematic.cpp"

    if string.startswith(prefix):
        string = string[len(prefix):]
    if string.endswith(suffix):
        string = string[:-len(suffix)]

    return string


def create_cpp_file(folder_name, file_name, content):
    try:
        os.makedirs(folder_name, exist_ok=True)
        file_path = os.path.join(folder_name, file_name + ".cpp")

        if not os.path.exists(file_path):
            with open(file_path, 'w') as file:
                file.write(content)
            print(f"C++ file '{file_path}' created successfully.")
        else:
            print(f"A file with the name '{file_name}.cpp' already exists in the folder '{folder_name}'. Skipping file creation.")
    except IOError:
        print(f"An error occurred while creating the C++ file '{file_path}'.")

def print_file_contents_recursive(folder_path):
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file.endswith(".cpp"):  # Filter only C++ files
                file_path = os.path.join(root, file)
                try:
                    with open(file_path, 'r') as file:
                        problemCodeDoubleArr = ["",""]
                        print("------------------------------AAAAAAAA------------------------------")
                        print(f"File: {file_path}")
                        contents = file.read()
                        problemCodeDoubleArr[0] = remove_prefix_suffix(file_path)
                        problemCodeDoubleArr[1] = contents
                        problematicCodeArr.append(problemCodeDoubleArr)
                except IOError:
                    print(f"An error occurred while reading the file '{file_path}'.")

# Example usage:
# Import your openai key to .env as "OPENAI_API_KEY"
load_dotenv()

print_file_contents_recursive('problematic')

classification = ""
code = ""

for problematicCodePiece in problematicCodeArr:
    classification = problematicCodePiece[0]
    code = problematicCodePiece[1]
    print(classification)

    # Set up your API credentials
    openai.api_key = os.getenv("OPENAI_API_KEY")

    # Define the input messages
    messages = [
        {"role": "system", "content": "You: Hello, how can I help you?"},
        {"role": "user", "content": "User message 1"}
    ]

    prompt1 = code + " There is a "+ classification + "problem in this code. Give me the fixed code that calculates runtime and ."
    prompt2 = " appends it as a new line into a file called runtime.txt. Make it write the runtime only and nothing else."
    prompt3 = " and don't write anything else other than the code." 
    prompt = prompt1 + prompt2 + prompt3

    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        temperature=0.2,
        max_tokens=1000,
        messages=[{"role": "user", "content": prompt}]
    )

    create_cpp_file("fixed/"+classification, "fixed", str(response.choices[0].message["content"]))

output_file = "runtimesFixed.txt"
execute_cpp_files_recursive("fixed", output_file)

output_file = "runtimesProblematic.txt"
execute_cpp_files_recursive("problematic", output_file)
