/******************************************************************************
 * Module: S2P
 * File Name: Program_arm_s2p_driver.c
 * Version: 1
 * Date: 13/2/2022
 * Description: function prototypes and variables and macro functions that can be called by user
 * Author: Zyad Ahmed Mackawy (ZAM)
 *******************************************************************************/

/* Private */

//--------------------------------------

/* Interface*/

// user config
// serial
#define S2P_serial_PORT A_u2_value_GPIOx_PORTS
#define S2P_serial_PIN 0
#define S2P_serial_PORT_clock_enable RCC_APB2ENR_IOPAEN_IO_port_A_clock_enable

// store clock
#define S2P_store_clock_PORT A_u2_value_GPIOx_PORTS
#define S2P_store_clock_PIN 1
#define S2P_store_clock_PORT_clock_enable RCC_APB2ENR_IOPAEN_IO_port_A_clock_enable

// shift clock
#define S2P_shift_clock_PORT A_u2_value_GPIOx_PORTS
#define S2P_shift_clock_PIN 2
#define S2P_shift_clock_PORT_clock_enable RCC_APB2ENR_IOPAEN_IO_port_A_clock_enable

// S2P functions

#define S2P_Byte(Data) S2P_Output(Data, 8)

#define S2P_Half_Word(Data) S2P_Output(Data, 16)

void S2P_Init(void)
{
    void_init_sysTick();
    MACRO_ENABLE_PERPH_RCC(RCC_APB2ENR_OFFSET, S2P_serial_PORT_clock_enable);
    void_init_output_push_pull_GPIO(S2P_serial_PORT, S2P_serial_PIN, OUTPUT_2_MHz_u2_value_GPIOx_PORTS);

    MACRO_ENABLE_PERPH_RCC(RCC_APB2ENR_OFFSET, S2P_store_clock_PORT_clock_enable);
    void_init_output_push_pull_GPIO(S2P_store_clock_PORT, S2P_store_clock_PIN, OUTPUT_2_MHz_u2_value_GPIOx_PORTS);

    MACRO_ENABLE_PERPH_RCC(RCC_APB2ENR_OFFSET, S2P_shift_clock_PORT_clock_enable);
    void_init_output_push_pull_GPIO(S2P_shift_clock_PORT, S2P_shift_clock_PIN, OUTPUT_2_MHz_u2_value_GPIOx_PORTS);
}

void S2P_Output(u16 Data, u8 byte_or_half_word)
{

    u8 i;

    MACRO_CONFIG_low_output_GPIO(S2P_shift_clock_PORT, S2P_shift_clock_PIN);

    for (i = byte_or_half_word; i > 0; i--)
    {

        if (GETBIT(Data, (i-1)))
        {

            MACRO_CONFIG_high_output_GPIO(S2P_serial_PORT, S2P_serial_PIN);
        }
        else
        {
            MACRO_CONFIG_low_output_GPIO(S2P_serial_PORT, S2P_serial_PIN);
        }

        MACRO_CONFIG_high_output_GPIO(S2P_shift_clock_PORT, S2P_shift_clock_PIN);
        void_delay_us_sysTick(2);
        MACRO_CONFIG_low_output_GPIO(S2P_shift_clock_PORT, S2P_shift_clock_PIN);
        void_delay_us_sysTick(2);
    }

    MACRO_CONFIG_high_output_GPIO(S2P_store_clock_PORT, S2P_store_clock_PIN);
    void_delay_us_sysTick(2);
    MACRO_CONFIG_low_output_GPIO(S2P_store_clock_PORT, S2P_store_clock_PIN);
    void_delay_us_sysTick(2);
}

//--------------------------------------
