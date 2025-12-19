import random
import numpy as np
import matplotlib.pyplot as plt

def random_LZ78(q : float):
    # =========1) c. Randomly generated sequence ========
    source = [] # make arbitrary 10^5 length binary list

    for j in range(10 ** 6):
        '''
        Add to the source '1' for probability 'q' and '0' for probability '1-q'
        using random function (random.random() generates float num between 0 and 1)
        '''
        if random.random() < q:
            source.append('1')
        else:
            source.append('0')
    print("".join(source))

    # =========1) a. LZ78 encoding program ========
    binary_input = source # take in input as array
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
    for k, v in encoded_tuple.items():
        print(k,':', v)

    R_c = (len(encoded_tuple) * (np.log2(len(encoded_tuple)) + 1)) / len(binary_input)
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

    #print("b) decoded sequence:",decoded_str)
    print("b) Is decoded sequence correct?:",decoded_str == "".join(source))
    return R_c
'''
# =========3) when q = 0.1 ========
random_LZ78(0.1)
'''
# =========4) plot Rc(q) and H(q) ========
def ent_q(q : float):
    return q*np.log2(1/q) + (1-q)*np.log2(1/(1-q))

q = np.arange(0.02, 0.3, 0.02) # make seemingly continuous q
R_c_vals = []
for q_val in q: # use q[1:-1] to avoid calculation error
    R_c_vals.append(random_LZ78(q_val))

plt.figure(figsize=(10, 4))
plt.plot(q, ent_q(q),label="H(q)")
plt.plot(q, R_c_vals, label="Rc(q)")
plt.title("H(q) (blue) and Rc(q) (orange) plot")
plt.xlabel("q")
plt.ylabel("Rc(q) and H(q)")
plt.xlim(0, 1)
plt.grid(True)
plt.show()