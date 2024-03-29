import handy
import cv2
import serial
import time

ArduinoSerial = serial.Serial('COM4',9600)

# getting video feed from webcam
cap = cv2.VideoCapture(0)

# capture the hand histogram by placing your hand in the box shown and
# press 'A' to confirm
# source is set to inbuilt webcam by default. Pass source=1 to use an
# external camera.
hist = handy.capture_histogram(source=0)

(xi,yi)=(0,0)

i=0
ctrl=False
register=True
j=5

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # to block a faces in the video stream, set block=True.
    # if you just want to detect the faces, set block=False
    # if you do not want to do anything with faces, remove this line
    handy.detect_face(frame, block=True)

    # detect the hand
    hand = handy.detect_hand(frame, hist)

    # to get the outline of the hand
    # min area of the hand to be detected = 10000 by default
    custom_outline = hand.draw_outline(
        min_area=10000, color=(0, 255, 255), thickness=2)

    # to get a quick outline of the hand
    quick_outline = hand.outline

    # draw fingertips on the outline of the hand, with radius 5 and color red,
    # filled in.
    for fingertip in hand.fingertips:
        cv2.circle(quick_outline, fingertip, 5, (0, 0, 255), -1)

    # to get the centre of mass of the hand
    com = hand.get_center_of_mass()
    if com:
        cv2.circle(quick_outline, com, 10, (255, 0, 0), -1)

    cv2.imshow("Handy", quick_outline)

    # display the unprocessed, segmented hand
    #cv2.imshow("Handy", hand.masked)

    # display the binary version of the hand
    #cv2.imshow("Handy", hand.binary)

    if com:
        if(i%4==0 and ctrl==False and register==True):
            if abs(com[0]-xi)>abs(com[1]-yi):
                if com[0]-xi>0:
                    print('Left')
                    ArduinoSerial.write(b'L')
                elif com[0]-xi<0:
                    print('Right')
                    ArduinoSerial.write(b'R')
            else:
                if com[0]-xi>0:
                    print('Down')
                    ArduinoSerial.write(b'D')
                elif com[0]-xi<0:
                    print('Up')
                    ArduinoSerial.write(b'U')
            ctrl=True
            j=8
        else:
            register=True
            ctrl=False
        (xi,yi)=com
    else:
        register=False
    if(i>=10):
        i=0
    i+=1

    if ctrl==True:
        j-=1

    if j==0:
        ctrl=False

    k = cv2.waitKey(5)

    # Press 'q' to exit
    if k == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()