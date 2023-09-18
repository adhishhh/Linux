import re
import sys

input_register_definitions = """
# ... Your register definitions ...
"""
def parse_unit_reg(unit_reg_id):
    match = re.search(r'LEP_CID_([a-zA-Z0-9]+)_(\w+)', unit_reg_id)
    if match:
        return match.group(1), match.group(2)
    return None, None
  
def parse_registers(register_definitions):
    registers = []
    lengths = {"AGC": {}, "OEM": {}, "RAD": {}, "SYS": {}, "VID": {}}

    for line in register_definitions.split('\n'):
        match = re.search(r'define\s+(\w+)\s+\(\w+\W+(\S+)', line)
        match2 = re.search(r'unit:(\w+)\s+register:(\d+)\s+length:(\d+)', line)

        if match:
            const, value = match.groups()
            value = ((int(value, 0) >> 2) & 0xFF) + 1
            registers.append((const, value))

        if match2:
            unit, register, length = match2.groups()
            lengths[unit][register] = length

    return registers, lengths

def unit_to_entity(unit):
    return f"UVC_GUID_LEP_{unit}_ID_CONTROL"

def format_constant(const, value):
    unit, reg = parse_unit_reg(const)
    offset = {"AGC": 0, "OEM": 1, "RAD": 2, "SYS": 3, "VID": 4}.get(unit, 5)
    
    return f"""
        <constant type="integer">
            <id>XU_{const}</id>
            <value>{value}</value>
        </constant>
        <constant type="integer">
            <id>V4L2_{const}</id>
            <value>0x{0x08000000 + (offset << 16) + value:08x}</value>
        </constant>
    """

def format_controls(registers, lengths):
    for register in registers:
        control = format_control(register, lengths)
        if control:
            print(control)

def format_control(register, lengths):
    unit_reg_id, value = register
    unit, reg = parse_unit_reg(unit_reg_id)
    entity = unit_to_entity(unit)
    length = int(lengths[unit].get(str(value), 0))
    requests = ""
    
    if length > 8:
        requests = "<request>SET_CUR</request>\n<request>GET_CUR</request>"
    elif length == 1:
        requests = "<request>SET_CUR</request>\n<request>GET_CUR</request>"
    else:
        requests = (
            "<request>SET_CUR</request>\n"
            "<request>GET_CUR</request>\n"
            "<request>GET_MIN</request>\n"
            "<request>GET_MAX</request>\n"
            "<request>GET_RES</request>"
        )
    
    return f"""
        <control id="{unit}_{reg}">
            <entity>{entity}</entity>
            <selector>XU_{unit_reg_id}</selector>
            <index>{(offset[unit] << 16) + (value - 1)}</index>
            <size>{length}</size>
            <requests>{requests}</requests>
            <description>Get/Set {unit} module register {reg}</description>
        </control>
    """

# Function to format mappings
def format_mappings(registers, lengths):
    for register in registers:
        mapping = format_mapping(register, lengths)
        if mapping:
            print(mapping)

# Function to format a mapping
def format_mapping(register, lengths):
    unit_reg_id, value = register
    unit, reg = parse_unit_reg(unit_reg_id)
    entity = unit_to_entity(unit)
    length = int(lengths[unit].get(str(value), 0))
    
    if length > 8:
        uvc_type = "UVC_CTRL_DATA_TYPE_RAW"
        v4l2_type = "V4L2_CTRL_TYPE_STRING"
    elif length == 1:
        uvc_type = "UVC_CTRL_DATA_TYPE_RAW"
        v4l2_type = "V4L2_CTRL_TYPE_BUTTON"
    else:
        uvc_type = "UVC_CTRL_DATA_TYPE_RAW"
        v4l2_type = "V4L2_CTRL_TYPE_INTEGER"
        length *= 8
    
    return f"""
        <mapping>
            <name>{unit_reg_id}</name>
            <uvc>
                <control_ref idref="{unit}_{reg}"/>
                <size>{length}</size>
                <offset>0</offset>
                <uvc_type>{uvc_type}</uvc_type>
            </uvc>
            <v4l2>
                <id>V4L2_{unit_reg_id}</id>
                <v4l2_type>{v4l2_type}</v4l2_type>
            </v4l2>
        </mapping>
    """

# Main function
def main():
    registers, lengths = parse_registers(input_register_definitions)
    
    print("""<?xml version="1.0" encoding="UTF-8"?>
<config version="1.0"
    xmlns="http://groupgets.com"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://groupgets.com uvcconfig.xsd">
    <meta>
        <version>3.3.13</version>
        <author>GetLab</author>
        <contact>contact@groupgets.com</contact>
        <revision>2</revision>
        <copyright>Copyright (c) GroupGets 2017 </copyright>
        <history>PureThermal 1 FLIR Lepton CCI XU control interface</history>
    </meta>
    <constants>
        <constant type="guid">
            <id>UVC_GUID_LEP_AGC_ID_CONTROL</id>
            <value>2d317470-656c-2d70-6167-632d30303030</value>
        </constant>
        <constant type="guid">
            <id>UVC_GUID_LEP_OEM_ID_CONTROL</id>
            <value>2d317470-656c-2d70-6f65-6d2d30303030</value>
        </
