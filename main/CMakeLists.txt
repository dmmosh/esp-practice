idf_component_register(SRCS "hello_world_main.c"
                    INCLUDE_DIRS ""
                    REQUIRES freertos
                    PRIV_REQUIRES nvs_flash spi_flash)
