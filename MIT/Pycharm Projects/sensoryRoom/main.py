# Title: sensory_room file.
# Author: Terrortronics / Bradley Elenbaas (mr.elenbaas@gmail.com)
# Version: 2
# Date: September 15, 2023
#
# Intellectual Property:
# Copyright (c) 2023 Bradley Elenbaas. All rights reserved.
#
# License:
# This file is owned by Terrortronics / Bradley Elenbaas.
# This file observes the MIT License.

"""
Copyright 2023 Bradley Elenbaas

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files
(the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""

import os
import random
import socket
import sys
import time

from gpiozero import Button
from gpiozero import Buzzer
from gpiozero import LED
import pygame


BACKGROUND_R = 248
BACKGROUND_G = 216
BACKGROUND_B = 8
CLOUDS_PERIOD_MAX = 120
CLOUDS_PERIOD_MIN = 60
CLOUDS_SPEED_X_MAX = 3
CLOUDS_SPEED_X_MIN = 4
CLOUDS_SPEED_Y_MAX = 0
CLOUDS_SPEED_Y_MIN = 1
CLOUDS_TOTAL = 40
FILENAME = 'udp_received.txt'
FRAMES_PER_SECOND = 60
IMAGE_MAX = 8
IMAGE_SIZE = 1024
IMAGE_SIZE_MAX = int(IMAGE_SIZE * 0.60)
IMAGE_SIZE_MIN = int(IMAGE_SIZE * 0.40)
KEYWORD = 'Cloud'

button = Button(2)
led = LED(25)
buzzer = Buzzer(15)


def get_path() -> str:
    path = ''
    if os.name == 'posix' and sys.platform == 'darwin':
        path += os.path.join(
            os.sep,
            'Applications',
            'PureBasic.app',
            'Contents',
            'Resources',
            'examples',
            '3d',
            'Data',
            'Textures')
    elif os.name == 'posix':
        path += os.path.join(
            os.sep,
            'home',
            os.getlogin(),
            'Apps',
            'purebasic_demo',
            'examples',
            '3d',
            'Data',
            'Textures')
    elif socket.gethostname() == 'DESKTOP-CR5GQ2G':
        path += os.path.join(
            'C:',
            os.sep,
            'Users',
            os.getlogin(),
            'OneDrive',
            'Desktop',
            'PureBasic',
            'Examples',
            '3D',
            'Data',
            'Textures')
    else:
        path += os.path.join(
            'C:',
            os.sep,
            'Users',
            os.getlogin(),
            'Desktop',
            'PureBasic',
            'Examples',
            '3D',
            'Data',
            'Textures')
    return path


def get_filename(path: str) -> str:
    length = 0
    cloud_filenames = []
    for root, directory, filenames in os.walk(path):
        for filename in filenames:
            if KEYWORD in filename:
                cloud_filenames.append(filename)
                length += 1
    length = random.randint(0, length - 1)
    return cloud_filenames[length]


def teardown():
    pygame.quit()


class Game:
    """PyGame specific calls."""

    def __init__(self):
        pygame.init()
        self.is_running = True
        self.__screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
        self.__clock = pygame.time.Clock()

    def blit(self, source: pygame.Surface, destingation: tuple):
        self.__screen.blit(source, destingation)

    def fill(self, color: tuple):
        self.__screen.fill(color)

    def input(self):
        """Close the window with [x] button or ESC"""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.is_running = False
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                self.is_running = False

    def get_height(self) -> int:
        return self.__screen.get_height()

    def get_width(self) -> int:
        return self.__screen.get_width()

    def update(self):
        pygame.display.update()
        self.__clock.tick(FRAMES_PER_SECOND)
        if button.is_held:
            print('ON')
            led.on()
            time.sleep(1)
            buzzer.on()
            time.sleep(1)
            os.system('sudo shutdown -r now')
        else:
            print('OFF')
            led.off()
            buzzer.off()


class Background:

    def __init__(self, game: Game):
        self.__game = game

    def update(self):
        messages = '0,0,0,'
        try:
            filename = os.path.expanduser('~/Desktop')
            filename = os.path.join(filename, FILENAME)
            with open(filename) as file:
                messages = file.readline()
            messages = messages.split(',')
            self.__game.fill((
                int(messages[0]),
                int(messages[1]),
                int(messages[2])))
        except OSError:
            messages = messages.split(',')
            self.__game.fill((
                int(messages[0]),
                int(messages[1]),
                int(messages[2])))


class Cloud:

    def __init__(self, game: Game, is_warming=True):
        self.__game = game
        self.__is_warming = is_warming
        self.__duration = 0.0
        self.__image = None
        self.__progress = 0.0
        self.__period_start = 0.0
        self.__start_x = 0.0
        self.__start_y = 0.0
        self.__stop_x = 0.0
        self.__stop_y = 0.0
        self.__x = 0.0
        self.__y = 0.0
        self.generate()

    def generate(self):
        filename = os.path.join(get_path(), get_filename(get_path()))
        print(filename)
        self.__image = pygame.image.load(filename)
        scale = random.randint(IMAGE_SIZE_MIN, IMAGE_SIZE_MAX)
        self.__image = pygame.transform.smoothscale(
            self.__image,
            (scale, scale))
        self.__duration = random.randint(
            CLOUDS_PERIOD_MIN,
            CLOUDS_PERIOD_MAX)
        self.__start_x = -self.__image.get_width()
        if self.__is_warming:
            self.__start_x += random.randint(
                0,
                self.__game.get_width())
            self.__is_warming = False
        self.__stop_x = self.__game.get_width()
        self.__stop_x += self.__image.get_width()
        self.__start_y = random.randint(
            -self.__image.get_height(),
            self.__game.get_height() + self.__image.get_height())
        self.__stop_y = random.randint(
            -self.__image.get_height(),
            self.__game.get_height() + self.__image.get_height())
        self.__period_start = time.time()

    def update(self):
        self.__progress = time.time() - self.__period_start
        self.__progress /= self.__duration
        if self.__progress >= 1.0:
            self.generate()
        self.__x = abs(self.__start_x)
        self.__x += abs(self.__stop_x)
        self.__x *= self.__progress
        self.__x += self.__start_x
        self.__x = int(self.__x)
        self.__y = abs(self.__start_y)
        self.__y += abs(self.__stop_y)
        self.__y *= self.__progress
        self.__y += self.__start_y
        self.__y = int(self.__y)
        self.__game.blit(self.__image, (self.__x, self.__y))


class Clouds:

    def __init__(self, game: Game):
        self.__game = game
        self.__clouds = self.__generate_clouds(CLOUDS_TOTAL)

    def __generate_clouds(self, length: int) -> list:
        self.__clouds = []
        for part in range(length):
            self.__clouds.append(Cloud(self.__game))
        return self.__clouds

    def update(self):
        for cloud in self.__clouds:
            cloud.update()


class Main:

    def __init__(self):
        self.__game = Game()
        self.__background = Background(self.__game)
        self.__clouds = Clouds(self.__game)

    def main(self):
        """The main function."""
        while self.__game.is_running:
            self.__game.input()
            self.__background.update()
            self.__clouds.update()
            self.__game.update()
        teardown()


if __name__ == '__main__':
    main = Main()
    main.main()
