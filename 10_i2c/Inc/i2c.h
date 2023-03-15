#ifndef I2C_H_
#define I2C_H_

void I2C1_init(void);
void I2C1_byte_read(char sAddr, char mAddr, char* data);
void I2C1_burst_read(char sAddr, char mAddr, int len, char* data);
void I2C1_burst_write(char sAddr, char mAddr, int len, char* data);

#endif /* I2C_H_ */
