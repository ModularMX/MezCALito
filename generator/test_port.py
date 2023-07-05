import pytest
import port

@pytest.fixture
def setup_pin():
    return port.PortPin( { "PortPinId": 0, "PortPinSymbolicName": "dio_1" } )

def test_GetPortPinId( setup_pin ):
    assert setup_pin.GetPortPinId() == 0

def test_GetPortPinSymbolicName( setup_pin ):
    assert setup_pin.GetPortPinSymbolicName() == "DIO_1"

def test_GetPortPinDirection( setup_pin ):
    assert setup_pin.GetPortPinDirection() == "PORT_MODE_INPUT"

def test_GetPortPinDirectionChangeable( setup_pin ):
    assert setup_pin.GetPortPinDirectionChangeable() == False

def test_GetPortPinInitialMode( setup_pin ):
    assert setup_pin.GetPortPinInitialMode() == "analog"

def test_GetPortPinMode( setup_pin ):
    assert setup_pin.GetPortPinMode() == "analog"

def test_GetPortPinLevelValue( setup_pin ):
    assert setup_pin.GetPortPinLevelValue() == "STD_LOW"

def test_GetPortPinModeChangeable( setup_pin ):
    assert setup_pin.GetPortPinModeChangeable() == False

def test_GetPortPinInputPullResistor( setup_pin ):
    assert setup_pin.GetPortPinInputPullResistor() == "PORT_RESISTOR_NOPULL"

def test_GetPortPinOutputPinDriveMode( setup_pin ):
    assert setup_pin.GetPortPinOutputPinDriveMode() == "PORT_PUSH_PULL"

def test_GetPortPinOutputSpeedMode( setup_pin ):
    assert setup_pin.GetPortPinOutputSpeedMode() == "PORT_SPEED_FREQ_LOW"


@pytest.fixture
def setup_PortContainer():
    test_container = { "PortNumber": "porta", "PortNumberOfPortPins": 16 }
    test_container["PortPin_0"] = { "PortPinId": 0, "PortPinSymbolicName": "portA_pin_0" }
    test_container["PortPin_1"] = { "PortPinId": 2, "PortPinSymbolicName": "portA_pin_2" }
    return port.PortContainer( test_container )
    
def test_GetPortNumber( setup_PortContainer ):
    assert setup_PortContainer.GetPortNumber() == 0

def test_GetPortNumberOfPortPins( setup_PortContainer ):
    assert setup_PortContainer.GetPortNumberOfPortPins() == 16

def test_GetDefaultPin( setup_PortContainer ):
    default_pin = { "PortPinId": 1, "PortPinSymbolicName": "PORT_0_PIN_1" }
    assert setup_PortContainer.GetDefaultPin(1) == default_pin

def test_GetPortPin_0( setup_PortContainer ):
    default_pin = { "PortPinId": 0, "PortPinSymbolicName": "portA_pin_0" }
    assert setup_PortContainer.GetPortPin(0) == default_pin

def test_GetPortPin_2( setup_PortContainer ):
    default_pin = { "PortPinId": 2, "PortPinSymbolicName": "portA_pin_2" }
    assert setup_PortContainer.GetPortPin(2) == default_pin

def test_GetPortPins( setup_PortContainer ):
    default_pins = [
        port.PortPin({ "PortPinId": 0, "PortPinSymbolicName": "portA_pin_0" }), port.PortPin({ "PortPinId": 1, "PortPinSymbolicName": "port_0_pin_1" }),
        port.PortPin({ "PortPinId": 2, "PortPinSymbolicName": "portA_pin_2" }), port.PortPin({ "PortPinId": 3, "PortPinSymbolicName": "port_0_pin_3" }),
        port.PortPin({ "PortPinId": 4, "PortPinSymbolicName": "port_0_pin_4" }), port.PortPin({ "PortPinId": 5, "PortPinSymbolicName": "port_0_pin_5" }),
        port.PortPin({ "PortPinId": 6, "PortPinSymbolicName": "port_0_pin_6" }), port.PortPin({ "PortPinId": 7, "PortPinSymbolicName": "port_0_pin_7" }),
        port.PortPin({ "PortPinId": 8, "PortPinSymbolicName": "port_0_pin_8" }), port.PortPin({ "PortPinId": 9, "PortPinSymbolicName": "port_0_pin_9" }),
        port.PortPin({ "PortPinId": 10, "PortPinSymbolicName": "port_0_pin_10" }), port.PortPin({ "PortPinId": 11, "PortPinSymbolicName": "port_0_pin_11" }),
        port.PortPin({ "PortPinId": 12, "PortPinSymbolicName": "port_0_pin_12" }), port.PortPin({ "PortPinId": 13, "PortPinSymbolicName": "port_0_pin_13" }),
        port.PortPin({ "PortPinId": 14, "PortPinSymbolicName": "port_0_pin_14" }), port.PortPin({ "PortPinId": 15, "PortPinSymbolicName": "port_0_pin_15" })
        ]
    port_pins = setup_PortContainer.GetPortPins()
    for i in range(16):
        assert port_pins[i].GetPortPinId() == default_pins[i].GetPortPinId()
        assert port_pins[i].GetPortPinSymbolicName() == default_pins[i].GetPortPinSymbolicName()
    