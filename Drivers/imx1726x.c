//device tree
/dts-v1/;
/plugin/;

/*device tree for the fuel gague*/

/{
        compatible = "brcm,bcm2708";
        framget@0 {
                  target = <&i2c_arm>;
                  __overlay__ {
                              #address-cells = <1>;
                              #size-cells = <0>;
                              status = "okay";
                              MAX1726x@36 {
                                        compatible = "maxim,MAX1726x";
                                        reg = <0x36>;
                                        rsense          = <10>;     /* miliOhm */
                                        model-option    = <1>;      /* Model 1, 2 or 3*/
                                        talrt-min   = <0>;          /* DegreeC */
                                        talrt-max   = <50>;         /* DegreeC */
                                        valrt-min   = <3000>;       /* mV */
                                        valrt-max   = <4500>;       /* mV */
                                        salrt-min   = <1>;          /* Percent */
                                        salrt-max   = <99>;         /* Percent */
                                        ialrt-min   = <(-5000)>;    /* mA */
                                        ialrt-max   = <5000>;       /* mA */


                                        /*** INI parameters ***/
                                        /* Option 1/2/3 */
                                        designcap   = /bits/ 16 <0x4E20>; /* 10000 mAh */
                                        ichgterm    = /bits/ 16 <0x0640>;
                                        vempty      = /bits/ 16 <0xA561>; /* 3300 mV */
                                        vcharge     = <4300>; /* mV */

                                        status = "okay";
                                        };
                              };
                };
};
