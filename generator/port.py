import schema
import yaml

port_schema = schema.Schema({
    "Port":
    {
        "PortConfigSet": {
            object: {
                "PortNumber": schema.Regex(r'port[a-f]'),
                "PortNumberOfPortPins": lambda n: 1 <= n <= 16,
                object: {
                    "PortPinId": lambda n: 0 <= n <= 15,
                    "PortPinSymbolicName": schema.Regex(r'^[a-zA-Z]\w'),
                    schema.Optional("PortPinDirection"): schema.Or("input", "output"),
                    schema.Optional("PortPinDirectionChangeable"): bool,
                    schema.Optional("PortPinInitialMode"): schema.Or("gpio", schema.Regex(r'alt[0-9]')),
                    schema.Optional("PortPinMode"): schema.Or("gpio", schema.Regex(r'alt[0-9]')),
                    schema.Optional("PortPinLevelValue"): schema.Or("low", "high"),
                    schema.Optional("PortPinModeChangeable"): bool,
                    schema.Optional("PortPinInputPullResistor"): schema.Or("nopull", "pullup", "pulldown"),
                    schema.Optional("PortPinOutputPinDriveMode"): schema.Or("pushpull", "opendrain"),
                    schema.Optional("PortPinOutputSpeedMode"): schema.Or("low", "medium", "high", "veryhigh"),
                }
            }
        },
        "PortGeneral": {
            "PortDevErrorDetect": bool,
            "PortSetPinDirectionApi": bool,
            "PortSetPinModeApi": bool,
            "PortVersionInfoApi": bool,
        }
    }
})

port_cfg_header = '''
/**
  * @file Port_Cfg.{0}
  * @brief Port configuration header file
  * 
  * This file contains the port configuration header file which is used to configure the port driver
  * the general port definitions and the port pin definitions in use set in the file port.yml.
  * 
  * @note This file is generated from the file port.yml and should not be modified manually
 */'''

port_cfg_guards = '''
#ifndef PORT_CFG_H
#define PORT_CFG_H
'''

port_cfg_number_of_ports = '''
/**
  * @brief Number of ports available in the MCU
  *
  * This define is used to specify the number of ports available in the MCU.
  */
#define PORT_NUMBER_OF_PORTS {0}
'''

port_cfg_dev_error = '''
/**
  * @brief Development error detection
  *
  * This define is used to enable the development error detection and report the errors to the
  * development error tracer module.
  */
#define PORT_DEV_ERROR_DETECT {0}
'''

port_cfg_pin_direction = '''
/**
  * @brief Port pin direction changeable
  *
  * This define is used to enable the port pin direction changeable feature.
  */
#define PORT_PIN_DIRECTION_CHANGEABLE {0}
'''

port_cfg_pin_mode = '''
/**
  * @brief Port pin mode changeable
  *
  * This define is used to enable the port pin mode changeable feature.
  */
#define PORT_PIN_MODE_CHANGEABLE {0}
'''

port_cfg_version_api = '''
/**
  * @brief Port driver version
  *
  * This define is used to specify the port driver version number.
  */
#define PORT_VERSION_INFO_API {0}
'''

port_cfg_footer = '''
#endif /* PORT_CFG_H */
'''

port_cfg_includes = '''
#include "Std_Types.h"
#include "Port.h"
'''

port_cfg_port_defines = '''
#define PORT_PA 0u
#define PORT_PB 1u
#define PORT_PC 2u
#define PORT_PD 3u
#define PORT_PE 4u
#define PORT_PF 5u

#define PORT_PA_NUMBER_OF_PINS      0xffff
#define PORT_PB_NUMBER_OF_PINS      0xffff
#define PORT_PC_NUMBER_OF_PINS      0xffff
#define PORT_PD_NUMBER_OF_PINS      0xffff
#define PORT_PE_NUMBER_OF_PINS      0xffff
#define PORT_PF_NUMBER_OF_PINS      0xffff
'''

port_cfg_pin_macros = '''
/**
 * @brief   set 8 values into a 4 bits each one
 */
#define PORT_SET_4BITS_VALUES( p7, p6, p5, p4, p3, p2, p1, p0 ) \\
    ( ( p7 ) << 28u ) | ( ( p6 ) << 24u ) | ( ( p5 ) << 20u ) | ( ( p4 ) << 16u ) | ( ( p3 ) << 12u ) | ( ( p2 ) << 8u ) | ( ( p1 ) << 4u ) | ( ( p0 ) << 0u )

/**
 * @brief   set 16 values into a 2 bits each one
 */
#define PORT_SET_2BITS_VALUES( p15, p14, p13, p12, p11, p10, p9, p8, p7, p6, p5, p4, p3, p2, p1, p0 )                                                             \\
    ( ( p15 ) << 30u ) | ( ( p14 ) << 28u ) | ( ( p13 ) << 26u ) | ( ( p12 ) << 24u ) | ( ( p11 ) << 22u ) | ( ( p10 ) << 20u ) | ( ( p9 ) << 18u ) | ( ( p8 ) << 16u ) | \\
    ( ( p7 ) << 14u ) | ( ( p6 ) << 12u ) | ( ( p5 ) << 10u ) | ( ( p4 ) << 8u ) | ( ( p3 ) << 6u ) | ( ( p2 ) << 4u ) | ( ( p1 ) << 2u ) | ( ( p0 ) << 0u )

/**
 * @brief   Set 16 values intop each bit
 */
#define PORT_SET_BITS_VALUES( p15, p14, p13, p12, p11, p10, p9, p8, p7, p6, p5, p4, p3, p2, p1, p0 )                                                            \\
    ( ( p15 ) << 15u ) | ( ( p14 ) << 14u ) | ( ( p13 ) << 13u ) | ( ( p12 ) << 12u ) | ( ( p11 ) << 11u ) | ( ( p10 ) << 10u ) | ( ( p9 ) << 9u ) | ( ( p8 ) << 8u ) | \\
    ( ( p7 ) << 7u ) | ( ( p6 ) << 6u ) | ( ( p5 ) << 5u ) | ( ( p4 ) << 4u ) | ( ( p3 ) << 3u ) | ( ( p2 ) << 2u ) | ( ( p1 ) << 1u ) | ( ( p0 ) << 0u )
'''

port_cfg_array = '''
/* clang-format off */
/* This data store Post-Build's Port Configuration Information. */
static const Port_PortsConfigType PortPortsConfig[ PORT_PIN_NUMBER_OF_PORTS ] =
{
    {0},
    {1},
    {2},
    {3},
    {4},
    {5}
};
/* clang-format on */
'''

port_cfg_port = '''
    { 
        .PortNumber          = {0},
        .AvailablePins       = {1},
        .{2},
        .{3},
        .{4},
        .{5},
        .{6},
        .{7},
        .{8},
        .{9}, 
        .{10},
    }
'''

port_cfg_initial_mode = '''
        .PortPinInitialMode          = PORT_SET_2BITS_VALUES( 
                {0}, {1}, {2}, {3}, 
                {4}, {5}, {6}, {7}, 
                {8}, {9}, {10}, {11}, 
                {12}, {13}, {14}, {15}
            ),
'''

port_cfg_output_drive = '''
        .PortPinOuputDrive   = PORT_SET_BITS_VALUES( 
                {0}, {1}, {2}, {3}, 
                {4}, {5}, {6}, {7}, 
                {8}, {9}, {10}, {11}, 
                {12}, {13}, {14}, {15} 
            ),
'''

port_cfg_speed = '''
        .PortPinSpeed        = PORT_SET_2BITS_VALUES( 
                {0}, {1}, {2}, {3}, 
                {4}, {5}, {6}, {7}, 
                {8}, {9}, {10}, {11}, 
                {12}, {13}, {14}, {15}
            ),
'''

port_cfg_resistor = '''
        .PortPinResistor     = PORT_SET_2BITS_VALUES( 
                {0}, {1}, {2}, {3}, 
                {4}, {5}, {6}, {7}, 
                {8}, {9}, {10}, {11}, 
                {12}, {13}, {14}, {15} 
            ),
'''

port_cfg_level = '''
        .PortPinLevelValue   = PORT_SET_BITS_VALUES( 
                {0}, {1}, {2}, {3}, 
                {4}, {5}, {6}, {7}, 
                {8}, {9}, {10}, {11}, 
                {12}, {13}, {14}, {15}
            ),
'''

port_cfg_alth = '''
        .PortPinAltH         = PORT_SET_4BITS_VALUES( 
                {0}, {1}, {2}, {3}, 
                {4}, {5}, {6}, {7}
            ),
'''

port_cfg_altl = '''
        .PortPinAltL         = PORT_SET_4BITS_VALUES( 
                {0}, {1}, {2}, {3}, 
                {4}, {5}, {6}, {7}
            ),
'''

port_cfg_dir_chg = '''
        .DirectionChangeable = 0x{0},
'''

port_cfg_mode_chg = '''
        .ModeChangeable      = 0x{0}
'''

port_cfg_const = '''
/* clang-format off */
/* This data store Post-Build's Port Configuration Information. */
const Port_ConfigType PortConfig =
{
    .PortNumbers = PORT_PIN_NUMBER_OF_PORTS,
    .PortsConfig = (Port_PortsConfigType*)&PortPortsConfig[ 0u ] 
};
/* clang-format on */
'''

class PortPin:
    def __init__( self, pin ):
        self.pin = pin

    def GetPortPinId( self ):
        return self.pin["PortPinId"]

    def GetPortPinSymbolicName( self ):
        return self.pin["PortPinSymbolicName"].upper()

    def GetPortPinDirection( self ):
        port_directions = { "input":"PORT_MODE_INPUT", "output":"PORT_MODE_OUTPUT" }
        return port_directions[self.pin.get("PortPinDirection", "input")]

    def GetPortPinDirectionChangeable( self ):
        return self.pin.get("PortPinDirectionChangeable", False)

    def GetPortPinInitialMode( self ):
        return self.pin.get("PortPinInitialMode", "analog")

    def GetPortPinMode( self ):
        return self.pin.get("PortPinMode", "analog")

    def GetPortPinLevelValue( self ):
        port_levels = { "high":"STD_HIGH", "low":"STD_LOW" }
        return port_levels[self.pin.get("PortPinLevelValue", "low")]

    def GetPortPinModeChangeable( self ):
        return self.pin.get("PortPinModeChangeable", False)

    def GetPortPinInputPullResistor( self ):
        port_resistors = { "pullup":"PORT_RESISTOR_PULLUP", "pulldown":"PORT_RESISTOR_PULLDOWN", "nopull":"PORT_RESISTOR_NOPULL" }
        return port_resistors[self.pin.get("PortPinInputPullResistor", "nopull")]

    def GetPortPinOutputPinDriveMode( self ):
        port_drive = { "pushpull":"PORT_PUSH_PULL", "opencolector":"PORT_OPEN_COLECTOR" }
        return port_drive[self.pin.get("PortPinOutputPinDriveMode", "pushpull")]

    def GetPortPinOutputSpeedMode( self ):
        port_speeds = { "low":"PORT_SPEED_FREQ_LOW", "medium":"PORT_SPEED_FREQ_MEDIUM", "high":"PORT_SPEED_FREQ_HIGH", "veryhigh":"PORT_SPEED_FREQ_VERY_HIGH" }
        return port_speeds[self.pin.get("PortPinOutputSpeedMode", "low")]


class PortContainer:
    def __init__(self, container):
        self.container = container
        self.port_numbers = { "porta":0, "portb":1, "portc":2, "portd":3, "porte":4, "portf":5 }
        self.cpy_container = self.container.copy() 
        del self.cpy_container["PortNumber"]
        del self.cpy_container["PortNumberOfPortPins"]

    def GetPortNumber( self ):
        return self.port_numbers[self.container["PortNumber"]]

    def GetPortNumberOfPortPins( self ):
        return self.container["PortNumberOfPortPins"]

    def GetPortPins( self ):
        pins = []
        for pin in range( 16 ):
            pins.append( PortPin( self.GetPortPin( pin ) ) )
        return pins

    def GetPortPin( self, pin ):
        flag = False
        for port_pin_name, port_pin in self.cpy_container.items():
            if port_pin["PortPinId"] == pin :
                flag = True
                break

        if flag == True :
            return port_pin
        else :
            return self.GetDefaultPin( pin )
        

    def GetDefaultPin( self, pin ):
        symbolic_name = "PORT_{0}_PIN_{1}".format( self.port_numbers[self.container["PortNumber"]], pin )
        return { "PortPinId": pin, "PortPinSymbolicName": symbolic_name }


class PortConfigSet:
    def __init__(self, config_set):
        self.config_set = config_set

    def GetPortContainers( self ):
        port_names = ["porta", "portb", "portc", "portd", "porte", "portf"]
        ports = []
        for port in port_names:
            ports.append( PortContainer( self.GetPortContainer( port ) ) )
        return ports

    def GetPortContainer( self, port ):
        flag = False
        for port_name, container in self.config_set.items():
            if container["PortNumber"] == port :
                flag = True
                break
        if flag == True :
            return container
        else :
            return self.GetDefaultContainer( port )

    def GetDefaultContainer( self, port ):
        port_numbers = { "porta":0, "portb":1, "portc":2, "portd":3, "porte":4, "portf":5 }
        default_container = { "PortNumber": port, "PortNumberOfPortPins": 16 }
        for pin in range( 16 ):
            default_container["PortPin_{0}".format( pin )] = { "PortPinId": pin, "PortPinSymbolicName": "port_{0}_pin_{1}".format( port_numbers[port], pin ) }
        return default_container


class PortGeneral:
    def __init__( self, general ):
        self.general = general
        self.array = ["STD_ON", "STD_OFF"]

    def GetPortDevErrorDetect( self ):
        return self.array[self.general["PortDevErrorDetect"]]

    def GetPortVersionInfoApi( self ):
        return self.array[self.general["PortVersionInfoApi"]]

    def GetPortSetPinDirectionApi( self ):
        return self.array[self.general["PortSetPinDirectionApi"]]

    def GetPortSetPinModeApi( self ):
        return self.array[self.general["PortSetPinModeApi"]]


class PortCfgH:
    def __init__( self ):
        self.Port_Cfg_h = open("Port_Cfg.h", "w")
        
    def WriteIncludeGuards( self ):
        self.Port_Cfg_h.write( port_cfg_header.format('h') )
        self.Port_Cfg_h.write( port_cfg_guards )
        self.Port_Cfg_h.write( "\n" )

    def WritePinNumberOfPorts( self, port_number_of_port_pins ):
        self.Port_Cfg_h.write( port_cfg_number_of_ports.format( port_number_of_port_pins ) )
        self.Port_Cfg_h.write( "\n" )

    def WriteDevErrorDetect( self, dev_error_detect ):
        self.Port_Cfg_h.write( port_cfg_dev_error.format( dev_error_detect ) )
        self.Port_Cfg_h.write( "\n" )

    def WriteSetPinDirectionApi( self, pin_direction ):
        self.Port_Cfg_h.write( port_cfg_pin_direction.format( pin_direction ) )
        self.Port_Cfg_h.write( "\n" )

    def WriteSetPinModeApi( self, pin_mode ):
        self.Port_Cfg_h.write( port_cfg_pin_mode.format( pin_mode ) )
        self.Port_Cfg_h.write( "\n" )

    def WriteVersionInfoApi( self, version_info_api ):
        self.Port_Cfg_h.write( port_cfg_version_api.format( version_info_api ) )
        self.Port_Cfg_h.write( "\n" )

    def WritePortPin( self, symbolic_name, port, pin ):
        string = "#define {0}                        ( Port_PinType )( 0x{1}{2} )".format( symbolic_name, format(port, '1x'), format(pin, '1x'))
        self.Port_Cfg_h.write( string )
        self.Port_Cfg_h.write( "\n" )

    def Close( self ):
        self.Port_Cfg_h.write( port_cfg_footer )
        self.Port_Cfg_h.write( "\n" )
        self.Port_Cfg_h.close()


class PortCfgC:
    def __init__( self ):
        self.Port_Cfg_h = open("Port_Cfg.c", "w")

    def WriteHeader( self ):
        self.Port_Cfg_h.write( port_cfg_header.format('c') )
        self.Port_Cfg_h.write( port_cfg_includes )
        self.Port_Cfg_h.write( "\n" )
        self.Port_Cfg_h.write( port_cfg_port_defines )
        self.Port_Cfg_h.write( "\n" )
        self.Port_Cfg_h.write( port_cfg_pin_macros )
        self.Port_Cfg_h.write( "\n" )

    def GetOutputDriveModeString( self, output_drive ):
        return port_cfg_output_drive.format( 
            output_drive[0], output_drive[1], output_drive[2], output_drive[3],
            output_drive[4], output_drive[5], output_drive[6], output_drive[7],
            output_drive[8], output_drive[9], output_drive[10], output_drive[11],
            output_drive[12], output_drive[13], output_drive[14], output_drive[15] 
            )

    def GetResistorModeString( self, resistors ):
        return port_cfg_resistor.format(
            resistors[0], resistors[1], resistors[2], resistors[3],
            resistors[4], resistors[5], resistors[6], resistors[7],
            resistors[8], resistors[9], resistors[10], resistors[11],
            resistors[12], resistors[13], resistors[14], resistors[15]
        )

    def GetSpeedModeString( self, speed ):
        return port_cfg_speed.format(
            speed[0], speed[1], speed[2], speed[3],
            speed[4], speed[5], speed[6], speed[7],
            speed[8], speed[9], speed[10], speed[11],
            speed[12], speed[13], speed[14], speed[15]
        )

    def GetInitialModeString( self, initial_mode ):
        return port_cfg_initial_mode.format(
            initial_mode[0], initial_mode[1], initial_mode[2], initial_mode[3],
            initial_mode[4], initial_mode[5], initial_mode[6], initial_mode[7],
            initial_mode[8], initial_mode[9], initial_mode[10], initial_mode[11],
            initial_mode[12], initial_mode[13], initial_mode[14], initial_mode[15]
        )

    def GetLevelModeString( self, level ):
        return port_cfg_level.format(
            level[0], level[1], level[2], level[3],
            level[4], level[5], level[6], level[7],
            level[8], level[9], level[10], level[11],
            level[12], level[13], level[14], level[15]
        )

    def GetAlthModeString( self, alth ):
        return port_cfg_alth.format(
            alth[0], alth[1], alth[2], alth[3],
            alth[4], alth[5], alth[6], alth[7],
            alth[8], alth[9], alth[10], alth[11],
            alth[12], alth[13], alth[14], alth[15]
        )

    def GetAltlModeString( self, altl ):
        return port_cfg_altl.format(
            altl[0], altl[1], altl[2], altl[3],
            altl[4], altl[5], altl[6], altl[7],
            altl[8], altl[9], altl[10], altl[11],
            altl[12], altl[13], altl[14], altl[15]
        )

    def GetDirModeStringChg( self, dir_chg ):
        dir_bits = 0
        for i in range( 0, 16 ):
            if dir_chg[i] == True:
                dir_bits |= 1 << i
        return str(format(port_cfg_dir_chg.format(dir_bits), '04x'))

    def GetModeModeStringChg( self, mode_chg ):
        mode_bits = 0
        for i in range( 0, 16 ):
            if mode_chg[i] == True:
                mode_bits |= 1 << i
        return str(format(port_cfg_dir_chg.format(mode_bits), '04x'))
    
    def GetPortStructure( self, port, pins, initial_mode, output_drive, speed, resistor, level, alth, altl, dir, mode ):
        return port_cfg_port.format(
            port, pins, initial_mode, output_drive, speed, resistor, level, alth, altl, dir, mode
        )

    def WriteConfigArray( self, port_array ):
        self.Port_Cfg_h.write( port_cfg_config_array.format(
            port_array[0], port_array[1], port_array[2],
            port_array[3], port_array[6], port_array[5]
        ) )
        self.Port_Cfg_h.write( "\n" )

    def Close( self ):
        self.Port_Cfg_h.write( port_cfg_const )
        self.Port_Cfg_h.write( "\n\n" )
        self.Port_Cfg_h.close()



def portGenerator():
    #open port configuration file and get the configuration
    port_file = open( 'port.yml', 'r' )
    port_yml = yaml.safe_load( port_file )
    port_file.close()

    #validates configuration with yml schema
    try:
        port_schema.validate( port_yml )
        # get the config set objects
        port_config_sets = PortConfigSet( port_yml["Port"]["PortConfigSet"] )
        # get the port global configs
        port_general = PortGeneral( port_yml["Port"]["PortGeneral"] )

        # generate the cfg header file
        port_cfg_h = PortCfgH()
        port_cfg_h.WriteIncludeGuards()
        port_cfg_h.WritePinNumberOfPorts( 6 )
        port_cfg_h.WriteDevErrorDetect( port_general.GetPortDevErrorDetect() )
        port_cfg_h.WriteSetPinDirectionApi( port_general.GetPortSetPinDirectionApi() )
        port_cfg_h.WriteSetPinModeApi( port_general.GetPortSetPinModeApi() )
        port_cfg_h.WriteVersionInfoApi( port_general.GetPortVersionInfoApi() )
        for port in port_config_sets.GetPortContainers():
            for pin in port.GetPortPins():
                port_cfg_h.WritePortPin( pin.GetPortPinSymbolicName(), port.GetPortNumber(), pin.GetPortPinId() )
        port_cfg_h.Close()

        # generate the cfg source file
        port_cfg_c = PortCfgC()
        port_cfg_c.WriteHeader()
        for port in port_config_sets.GetPortContainers():
            init_modes = []
            resistors = []
            drives = []
            sppeds = []
            levels = []
            dir_chgs = []
            mode_chgs = []
            alths = []
            altls = []

            for pin in port.GetPortPins():
                init_modes.append(pin.GetPortPinInitialMode())
                resistors.append(pin.GetPortPinInputPullResistor())
                drives.append(pin.GetPortPinOutputCurrentDrive())
                sppeds.append(pin.GetPortPinOutputCurrentSpeed())
                levels.append(pin.GetPortPinLevelValue())
                dir_chgs.append(pin.GetPortPinDirectionChangeable())
                mode_chgs.append(pin.GetPortPinModeChangeable())
                alths.append(pin.GetPortPinAlternateFunctionHigh())
                altls.append(pin.GetPortPinAlternateFunctionLow())

            init_modes_string = port_cfg_c.GetInitModeString( init_modes )
            resistors_string = port_cfg_c.GetResistorModeString( resistors )
            drives_string = port_cfg_c.GetDriveModeString( drives )
            speeds_string = port_cfg_c.GetSpeedModeString( sppeds )
            levels_string = port_cfg_c.GetLevelModeString( levels )
            dir_chgs_string = port_cfg_c.GetDirModeStringChg( dir_chgs )
            mode_chgs_string = port_cfg_c.GetModeModeStringChg( mode_chgs )
            alths_string = port_cfg_c.GetAlthModeString( alths )
            altls_string = port_cfg_c.GetAltlModeString( altls )
        
            structure = port_cfg_c.GetPortStructure( "PORT_PA", "PORT_PA_NUMBER_OF_PINS", init_modes, drives_string, speeds_string, resistors_string, levels_string )
        
        port_cfg_c.WriteConfigArray( structure )    
        port_cfg_c.Close()

    except schema.SchemaError as se:
        raise se


if __name__ == "__main__":
    portGenerator()
