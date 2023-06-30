import yaml

class PortPins:
    def __init__( self, Pin ):
        self.Pin = Pin

    def GetPortPinId( self ):
        return self.Pin["PortPinId"]

    def GetPortPinSymbolicName( self ):
        return self.Pin["PortPinSymbolicName"]

    def GetPortPinDirection( self ):
        return self.Pin["PortPinDirection"]

    def GetPortPinDirectionChangeable( self ):
        return self.Pin["PortPinDirectionChangeable"]

    def GetPortPinInitialMode( self ):
        return self.Pin["PortPinInitialMode"]

    def GetPortPinMode( self ):
        return self.Pin["PortPinMode"]

    def GetPortPinLevelValue( self ):
        return self.Pin["PortPinLevelValue"]

    def GetPortPinModeChangeable( self ):
        return self.Pin["PortPinModeChangeable"]

    def GetPortPinInputPullResistor( self ):
        return self.Pin["PortPinInputPullResistor"]

    def GetPortPinOutputPinDriveMode( self ):
        return self.Pin.get( "PortPinOutputPinDriveMode", "pushpull" )
      

class PortContainers:
    def __init__(self, Container):
        self.Container = Container

    def GetPortNumber( self ):
        return self.Container["PortNumber"]

    def GetPortNumberOfPortPins( self ):
        return self.Container["PortNumberOfPortPins"]

    def GetPortPins( self ):
        CpyContainer = self.Container
        del CpyContainer["PortNumber"]
        del CpyContainer["PortNumberOfPortPins"]
        array = []
        for port, set in CpyContainer.items():
            array.append( PortPins( set ) )
        return array

class PortConfigSet:
    def __init__(self, ConfigSet):
        self.ConfigSet = ConfigSet

    def GetPortContainers( self ):
        array = []
        for port, set in self.ConfigSet.items():
            array.append( PortContainers( set ) )
        return array

file = open( 'port.yml', 'r' )
port = yaml.safe_load( file )

PortConfigSets = port.get( "PortConfigSet" )
PortContainer = PortConfigSets.get( "PortContainer_0" )
print( PortContainer.get( "PortNumber" ) )
print( PortContainer.get( "PortNumberOfPortPins" ) )
PortPin = PortContainer.get("PortPin_1")
print( PortPin.get( "PortPinSymbolicName" ) )

PortConfigSets = PortConfigSet( port["PortConfigSet"] )
PortContainer = PortConfigSets.GetPortContainers()
print( PortContainer[0].GetPortNumber() )
print( PortContainer[0].GetPortNumberOfPortPins() )
PortPin = PortContainer[0].GetPortPins()
print( PortPin[0].GetPortPinSymbolicName() )




