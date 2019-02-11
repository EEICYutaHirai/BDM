import serial
import subprocess

if __name__ == '__main__':
    s = serial.Serial('/dev/ttyACM0', 9600)
    while(True):
        if(s.readline() == 'start\r\n'):
            x = []
            for i in range(1025):
                x.append(int(s.readline()))
            f = open('data.txt', 'w')
            for i in x:
                f.write(str(i) + "\n")
            f.close()
            res = subprocess.check_output('./fft_get_speed<data.txt')
            s.write("res\n")
