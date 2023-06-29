import core

need_hide_data = '这是一段LSB隐藏数据'.encode('utf-8')  # 需要隐藏的数据
encrypt_key = '这是加密用的密钥'.encode('utf-8')  # 加密密钥
print("原始数据:{}".format(need_hide_data.decode('utf-8')))
print("加密密钥:{}".format(encrypt_key.decode('utf-8')))

src_path = 'src/pic.bmp'  # 原始图片
tar_path = 'src/pic_new.bmp'  # 隐藏数据后的图片
tar_path_enc = 'src/pic_new_enc.bmp'  # 加密后隐藏数据的图片

# 打开文件
with open(src_path, 'rb') as f:
    data = f.read()

# 1.隐藏数据
new_data = core.hide_lsb(data, need_hide_data)

# 保存文件
with open(tar_path, 'wb') as f:
    f.write(new_data)
print("隐藏数据完成:{}".format(need_hide_data.decode('utf-8')))

# 2.恢复数据
restore_data = core.restore_lsb(new_data)
print("恢复数据成功:{}".format(restore_data.decode('utf-8')))

# 3.对数据先加密, 再隐藏
need_hide_data_enc = core.aes_encrypt(need_hide_data, encrypt_key)
# 输出加密后的数据
print("加密后的数据:")
for i in range(0, len(need_hide_data_enc)):
    print(hex(need_hide_data_enc[i]), end=' ')
print()
# 隐藏加密后的数据
new_data = core.hide_lsb(data, need_hide_data_enc)
with open(tar_path_enc, 'wb') as f:
    f.write(new_data)
print("隐藏数据完成:{}".format(need_hide_data.decode('utf-8')))

# 4.恢复数据
restore_data = core.restore_lsb(new_data)
# 解密数据
restore_data = core.aes_decrypt(restore_data, encrypt_key)
print("恢复数据成功:{}".format(restore_data.decode('utf-8')))
