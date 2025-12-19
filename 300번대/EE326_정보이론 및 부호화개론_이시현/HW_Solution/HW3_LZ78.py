import math

# =========1) a. LZ78 encoding program ========
binary_input = list(input("")) # take in input as array
encoded_tuple = {} # make empty dictionary, the result of LZ78
i = 0

while i < len(binary_input): 
    '''
    Use y as position of current position
    Add next number to x until x does not exist in key_list
    Add x to dictionary
    As noticed in notification in klms, if the last x is not new,
    I used '2' as the last number that x has.
    '''
    x = binary_input[i]
    y = i
    key_list = list(encoded_tuple.keys())
    while x in key_list:
        if y < len(binary_input) - 1:
            x += binary_input[y+1]
            y += 1
        else: 
            encoded_tuple[x+'2'] = (key_list.index(x) + 1, 2)
            break
    if y == i:
        encoded_tuple[x] = (0, int(x))
    else:
        encoded_tuple[x] = (key_list.index(x[:-1]) + 1, int(x[-1]))
    i = y + 1
print("1. a) encoded tuples")
for k, v in encoded_tuple.items(): #print every keys and values in each line
    print(k,':', v)

R_c = (len(encoded_tuple) * (math.log2(len(encoded_tuple)) + 1)) / len(binary_input) #Rc calculation
print("Rc = ",R_c)
# example input: 10010010001101011, 0, 01, 001010011111

# =========1) b. LZ78 encoding program ========
decoded_str = ''
tuple_list = list(encoded_tuple.values())
reconst_dict = {}
for t in tuple_list:
    '''
    Reconstruct the dictionary from tuples.
    If there is tuple that has '2', add decoded_str the string without '2'.
    '''
    if t[1] == 2:
        reconst_dict[list(reconst_dict.keys())[t[0]-1]+'2'] = t
        break
    if t[0] == 0:
        reconst_dict[str(t[1])] = t
    else: 
        reconst_dict[list(reconst_dict.keys())[t[0]-1]+str(t[1])] = t

for v in tuple_list:
    '''
    From reconstructed dictionary, add decoded_str a corresponding string.
    '''
    if v[1] == 2:
        decoded_str += list(reconst_dict.keys())[v[0]-1]
        break
    if v[0] == 0:
        decoded_str += str(v[1])
    else: decoded_str += list(reconst_dict.keys())[v[0]-1] + str(v[1])

print("b) decoded sequence:",decoded_str)
print("   Is decoded sequence correct?:",decoded_str == "".join(binary_input))