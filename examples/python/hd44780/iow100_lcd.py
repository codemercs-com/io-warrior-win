import hid
import time

class IOW100_LCD:
    """Wrapper für HID-Gerätezugriff."""

    IOW100_REPORT_LEN_SPECIAL = 64

    ENABLE_ID = 0x04
    REPORT_ID = 0x05

    RS_INSTRUCTION = 0x00
    RS_DATA = 0x80

    LCD_CLEAR = 0x01
    LCD_HOME = 0x02

    
    def __init__(self, vendor_id, product_id, interface_number=None):
        self.vendor_id = vendor_id
        self.product_id = product_id
        self.interface_number = interface_number
        self._device = None

    def _find_device_path(self):
        """Findet den Pfad für das Gerät mit passender Interface-Nummer."""
        devices = hid.enumerate(self.vendor_id, self.product_id)

        for dev in devices:
            if dev.get("interface_number") == self.interface_number:
                return dev.get("path")
            
        return None
    
    def connect(self):
        """Verbindung zum Gerät herstellen."""
        if self._device:
            return True  # Bereits verbunden
        
        try:
            self._device = hid.device()
            
            if self.interface_number is not None:
                # Gerät mit spezifischer Interface-Nummer suchen
                path = self._find_device_path()
                if path:
                    self._device.open_path(path)
                else:
                    raise IOError(f"Gerät mit Interface {self.interface_number} nicht gefunden")
            else:
                # Einfach per VID/PID öffnen
                self._device.open(self.vendor_id, self.product_id)
            
            return True
        except Exception as e:
            self._device = None
            raise IOError(f"Verbindung fehlgeschlagen: {e}")
    
    def disconnect(self):
        """Verbindung trennen."""
        if self._device:
            self._device.close()
            self._device = None

    def enable(self, status):
        """Enable ICD interface"""
        if not self._device:
            raise IOError("Nicht verbunden")
        
        data = [self.ENABLE_ID, status]
        return self._device.write(data)
    
    def write(self, data):
        """Daten senden. data = Liste von Bytes."""
        if not self._device:
            raise IOError("Nicht verbunden")

        report = [self.REPORT_ID, self.RS_INSTRUCTION | 0x01] + data
        return self._device.write(report)
    
    def read(self, length=IOW100_REPORT_LEN_SPECIAL, timeout_ms=1000):
        """Daten empfangen."""
        if not self._device:
            raise IOError("Nicht verbunden")
        
        return self._device.read(length, timeout_ms)
    
    def write_string(self, text, encoding="ascii"):
        """String als HID-Report senden."""
        if not self._device:
            raise IOError("Nicht verbunden")
    
        text_bytes = list(text.encode(encoding))
        length = len(text_bytes)

        data = [self.REPORT_ID, self.RS_DATA | length] + text_bytes
        return self._device.write(data)
    
    # Context-Manager Support (für "with"-Statement)
    def __enter__(self):
        self.connect()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.disconnect()
        return False