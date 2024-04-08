# RFID Door Access Control System

## Demonstration:
Click on the link -->
   https://github.com/Jojo-Rod/Smart_Door_Lock/issues/3#issue-2231888452

## Components Used:

- MFRC522 RFID module
- LiquidCrystal I2C display (for user feedback)
- Buzzer (for alerting unauthorized access attempts)

## Operation:

1. When a card is scanned, the system reads the card's Unique Identifier (UID).
2. The UID is compared against an authorized card ID.
3. If the scanned card is authorized, the relay is activated to unlock the door for a set duration.
4. If the scanned card is not authorized, a buzzer is activated to indicate denial of access.
5. User feedback, including status messages and access granted/denied notifications, is displayed on the LiquidCrystal I2C display.

## Key Features:

- Secure door access control using RFID technology
- Visual feedback through the LCD display
- Audible alert for unauthorized access attempts

## Future Scope & Improvements:
This project provides a basic framework for implementing a door access control system using Arduino and RFID technology. It can be extended and customized based on specific requirements and additional features desired.

Contributors:

[Johanna Rodrigues] - Developer
