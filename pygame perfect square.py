import pygame
import math

pygame.init()
WIDTH, HEIGHT = 600, 600
win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Perfect Square Path")
clock = pygame.time.Clock()


x, y = 300, 300
theta = 0
v = 100  
w = math.radians(90)  
side_time = 2         
turn_time = 1         

commands = [
    ('forward', side_time),
    ('turn', turn_time),
    ('forward', side_time),
    ('turn', turn_time),
    ('forward', side_time),
    ('turn', turn_time),
    ('forward', side_time),
    ('turn', turn_time),
]


robot_path = [(x, y)]
current_cmd = 0
time_counter = 0
FPS = 60

running = True
while running:
    dt = clock.tick(FPS) / 1000
    time_counter += dt

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    if current_cmd < len(commands):
        action, duration = commands[current_cmd]

        if action == 'forward':
            x += v * math.cos(theta) * dt
            y += v * math.sin(theta) * dt
        elif action == 'turn':
            theta += w * dt

        robot_path.append((x, y))

        if time_counter >= duration:
            current_cmd += 1
            time_counter = 0

    win.fill((255, 255, 255))  
    if len(robot_path) > 1:
        pygame.draw.lines(win, (0, 0, 255), False, robot_path, 2)

    pygame.draw.circle(win, (0, 200, 0), (int(x), int(y)), 8)
    pygame.display.update()

pygame.quit()
