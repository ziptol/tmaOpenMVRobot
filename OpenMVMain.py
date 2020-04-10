#OpenMVMain - By: Zack Perry - Fri April 10, 2020

import sensor, image, time
from pyb import LED, UART

EXPOSURE_TIME_SCALE = 0.08

#Sensor settings
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
led = LED(2);
led.on()

current_exposure_time_in_microseconds = sensor.get_exposure_us()
sensor.set_auto_exposure(False, \
    exposure_us = int(current_exposure_time_in_microseconds * EXPOSURE_TIME_SCALE))

clock = time.clock()

uart = UART(3, 57600)

#main loop
while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs([(30, 100, -70, -8, -20, 60)], pixels_threshold=200, area_threshold=100, merge=True):
        # These values are stable all the time.
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        uart.write(str(blob.cx())+"\n")

