import serial
import subprocess
import os
import shlex

if __name__ == '__main__':
    s = serial.Serial('/dev/ttyACM0', 115200)
    print("connected")
    while(True):
        text = s.readline()
        #print(str(text))
        if(str(text).find('start')>-1):
            x = []
            #1024+2
            for i in range(1026):
                x.append(int(s.readline()))
                #print(x[i])
            f = open('data.txt', 'w')
            #print("make txt")
            for i in range(len(x)):
                f.write(str(x[i]) + "\n")
            f.close()
            '''
            Ec = float(subprocess.check_output('./fft_get_speed'))
            print("Ec:"+str(Ec))
            pwm = s.readline()
            print("pwm:"+str(int(pwm)))
            limit = s.readline()
            print("limit pwm: " + str(float(limit)))
            is_braked = s.readline()
            print("brake:" + str(is_braked))
            print()
            '''
            pwm = int(subprocess.check_output('./cal_pwm'))
            print("pwm:" + str(pwm))
            s.write((str(pwm)+'\n').encode())
            #print("want to send this")
            #print(str(res).encode())
            #test_text = s.readline()
            #print("response:" + str(test_text))

