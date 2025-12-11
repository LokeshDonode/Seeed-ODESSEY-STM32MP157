# How to Auto-Start a Script on Boot (Systemd)

This guide documents how to create a `systemd` service to automatically run a script (Python or Bash) when the Embedded Linux system boots.

## Prerequisites
1. **The Script**: Ensure your script exists and you know the absolute path (e.g., `/home/debian/user_leds_toggle.sh`).
2. **Permissions**: The script must be executable.
   ```bash
   chmod +x /home/debian/gpio_user_leds_toggle.sh

Step 1: Create the Service Unit File
The service file must be placed in /etc/systemd/system/.

1. Create/Edit the file:
$sudo nano /etc/systemd/system/user_leds_toggle.service

2. Paste the following configuration. IMPORTANT: Do not add comments on the same line as the commands (inline comments causes syntax errors).

```
[Unit]
Description=User LEDs Toggle Service
After=network.target

[Service]
Type=simple
# Replace the path below with your actual script path
ExecStart=/usr/bin/python3 /home/debian/user_leds_toggle.py
Restart=on-failure
User=root

[Install]
WantedBy=multi-user.target

```
3. Save and Exit (Ctrl+O, Enter, Ctrl+X).

Step 2: Enable the Service

# 1. Reload systemd to recognize the new file
$sudo systemctl daemon-reload

# 2. Enable the service to run on boot
$sudo systemctl enable user_leds_toggle.service

Step 3: Start and Verify

You can start the service immediately without rebooting to test it.

# 1. Start the service
$sudo systemctl start user_leds_toggle.service

# 2. Check the status
$sudo systemctl status user_leds_toggle.service

If successful, you should see: Active: active (running).


>> Error: "Unit file does not exist"
Cause: The file is in the wrong folder. Fix: You likely put it in /etc/systemd/. Move it to the system folder:

$sudo mv /etc/systemd/user_leds_toggle.service /etc/systemd/system/
