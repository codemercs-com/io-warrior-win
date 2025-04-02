# USB_HID_Devices_Filtered.ps1
# This script lists only currently connected USB and HID devices with a specific VID
# including PID and device name/description.
# Note: Some queries may require administrative rights.

# Define the VID to filter by (without "0x" prefix)
$filterVID = "07C0"

# Query both device categories: USBDevice and HIDClass
# Status "OK" means the device is currently connected and operational
$devices = Get-PnpDevice -Class USBDevice, HIDClass | Where-Object { $_.Status -eq "OK" }

$filteredDevices = $devices | ForEach-Object {
    # Use FriendlyName if available, otherwise use Name
    $name = if ($_.FriendlyName) { $_.FriendlyName } else { $_.Name }
    
    # Try to extract VID and PID from the InstanceId (case insensitive)
    if ($_.InstanceId -match "(?i)VID_([0-9A-F]+)&PID_([0-9A-F]+)") {
        $vidValue = $matches[1]
        $pidValue = $matches[2]
        
        # Check if the VID matches our filter
        if ($vidValue -eq $filterVID) {
            [PSCustomObject]@{
                "Name"       = $name
                "VID"        = $vidValue
                "PID"        = $pidValue
                "Status"     = $_.Status
                "InstanceID" = $_.InstanceId
            }
        }
    }
}

if ($filteredDevices) {
    Write-Host "Currently connected devices with VID = $($filterVID)" -ForegroundColor Green
    $filteredDevices | Format-Table -AutoSize
} else {
    Write-Host "No connected devices with VID = $($filterVID) found." -ForegroundColor Yellow
}