nASCII_dict = {
    'ã':'a',
    'á':'a',
    'à':'a',
    'Á':'A',
    'À':'A',
    'ç':'c',
    'Ç':'C',
    'é':'e',
    'ê':'e',
    'É':'E',
    'Ê':'E',
    'í':'i',
    'Í':'I',
    'Ó':'O',
    'Ô':'O',
    'ó':'o',
    'ô':'o',
    'Ú':'U',
    'ú':'u',
    }

def correct_char(c):
    for ch in nASCII_dict.keys():
        if ch == c:
            return nASCII_dict[ch]

    return c
    

#main

input_file = open("file.txt", 'r')
output_file = open("ASCII_text.txt", 'w')

while(True):
    character = input_file.read(1)
    if(character == ''):
        break

    output_file.write(correct_char(character))

input_file.close()
output_file.close()
