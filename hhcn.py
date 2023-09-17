import math

area1, area2, area3 = map(int, input().split())

length = math.sqrt(area1 * area2 / area3)
width = math.sqrt(area2 * area3 / area1)
height = math.sqrt(area3 * area1 / area2)

sum_of_edges = 4 * (length + width + height)

print(int(sum_of_edges))