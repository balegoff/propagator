import os, sys

repo_name = 'propagator'

wc_dir = os.getcwd()

# Check launch folder
if not os.path.isfile(repo_name + '/generate.py'):	
	sys.exit('[Error] This script must be launched from parent folder (workspace)')

dependencies = ['serialib', 'nanovg', 'glfw']

repos = {
	"serialib": "https://github.com/imabot2/serialib.git",
	"nanovg": "https://github.com/memononen/nanovg.git",
	"glfw": "https://github.com/glfw/glfw.git"
}

# Clone dependencies
for dep in dependencies:
    if not os.path.exists(dep):
    	os.system('git clone ' + repos[dep])
