import random
import numpy as np
import matplotlib.pyplot as plt

def hamming743(p : float):
    '''
    0) form a parity check matrix H
    '''
    H = np.array([
        [0,0,0,1,1,1,1],
        [0,1,1,0,0,1,1],
        [1,0,1,0,1,0,1]
    ])
    msg_list = []
    output_list = []
    for _ in range(10**6):
        '''
        a) make 10^6 length-4 binary codeword
        '''
        msg_list.append(list(map(int, f"{random.randint(0, 15):04b}")))
    
    for msg in msg_list:
        '''
        b) for each massage, make codeword
        used p1=b+c+d, p2=a+c+d, p3=a+b+d
        and according to p and BSC, send codeword
        '''
        msg.append((msg[1]+msg[2]+msg[3])%2)
        msg.append((msg[0]+msg[2]+msg[3])%2)
        msg.append((msg[0]+msg[1]+msg[3])%2)
        output_list.append(msg.copy())
        for i in range(7):
            if random.random() < p:
                msg[i] = (msg[i] + 1) % 2
    temp = msg_list
    msg_list = output_list
    output_list = temp

    '''
    c) if Hr == 0, estimate as r.
    if Hr != 0, correct r.
    '''
    count_undetected = 0
    count_corrected = 0
    count_not_single_error = 0
    for i in range(10**6):
        Hr = np.dot(H, np.array(output_list[i])) % 2
        h_i = Hr[0] * 4 + Hr[1] * 2 + Hr[2]
        if h_i != 0:
            output_list[i][h_i - 1] = (output_list[i][h_i - 1] + 1) % 2
            if output_list[i] == msg_list[i]:
                count_corrected += 1
            else: count_not_single_error += 1
        else:
            if output_list[i] != msg_list[i]:
                count_undetected += 1
    
    '''
    d) e) f) g)calculate the probability and plot it
    '''
    P_u = count_undetected / 10**6
    P_dc = count_corrected / 10**6
    P_du = count_not_single_error / 10**6
    P_t = P_u + P_du
    return P_u, P_dc, P_du, P_t

def plot_hamming(p_values):
    prob_undetected = []
    prob_corrected = []
    prob_not_single_error = []
    prob_total = []
    for p in p_values:
        P_u, P_dc, P_du, P_t = hamming743(p)
        prob_undetected.append(P_u)
        prob_corrected.append(P_dc)
        prob_not_single_error.append(P_du)
        prob_total.append(P_t)

    data_to_plot = [
        (prob_undetected, "P(undetected error) - (d)"),
        (prob_corrected, "P(error corrected) - (e)"),
        (prob_not_single_error, "P(correction failed) - (f)"),
        (prob_total, "P(total error) - (g)")
    ]

    fig, axes = plt.subplots(2, 2, figsize=(12, 8))
    fig.suptitle("Hamming Code Performance (Log Scale)", fontsize=16)

    for ax, (data, title) in zip(axes.flat, data_to_plot):
        ax.plot(p_values, data, 'o-')
        ax.set_title(title)
        ax.set_xlabel("Channel Error Probability (p)")
        ax.set_ylabel("Probability (log scale)")
        ax.set_yscale('log')
        ax.grid(True, which="both", linestyle="--")
        ax.set_xlim(min(p_values) - 0.01, max(p_values) + 0.01) 

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.show()

plot_hamming(np.arange(0.01, 0.10, 0.01))
plot_hamming(np.arange(0.1, 0.6, 0.1))