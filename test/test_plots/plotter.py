import matplotlib.pyplot as plt
import matplotlib.patches as patches

# Input rectangle data
data = {
    "rects": [ 
        {"x": -100, "y": -100, "w": 250, "h": 80},  
        {"x": -140, "y": -160, "w": 250, "h": 100},  
    ],
    "inter": [ 
        {"x": -100, "y": -100, "w": 210, "h": 40},  
    ],
}

# Set up plot
fig, ax = plt.subplots()
ax.set_aspect('equal')
ax.set_title("TEST1")
ax.set_xlabel("X-axis")
ax.set_ylabel("Y-axis")

ax.set_xlim(-600, 600) 
ax.set_ylim(-450, 450)
ax.invert_yaxis() # origin is top-left, y grows down

ax.grid(True, which='both', linestyle='--', linewidth=0.5, color='lightgray')

# Draw rectangles
for rect in data["rects"]:
    patch = patches.Rectangle(
        (rect["x"], rect["y"]),
        rect["w"], rect["h"],
        linewidth=1,
        edgecolor='black',
        facecolor=(1, 0, 0, 0.3)  
    )
    ax.add_patch(patch)

# Draw intersections
for inter in data["inter"]:
    patch = patches.Rectangle(
        (inter["x"], inter["y"]),
        inter["w"], inter["h"],
        linewidth=1,
        edgecolor='green',
        facecolor=(1, 0, 0, 0)  
    )
    ax.add_patch(patch)

plt.tight_layout()
plt.show()
