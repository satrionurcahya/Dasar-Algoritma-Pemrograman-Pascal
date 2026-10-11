# =====================================================
# TUGAS 13.4 - SOAL 2
# jumlah = 1 + 2 + ... + n, dengan n = 10
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanJumlah : .asciiz "Jumlah 1 sampai n = "

.text
.globl main

main:
    li   $t0, 1         # $t0 = i = 1
    li   $t1, 10        # $t1 = n = 10
    li   $t2, 0         # $t2 = jumlah = 0

loop:
    # Cek: i <= n ?
    bgt  $t0, $t1, selesai

    # jumlah = jumlah + i
    add  $t2, $t2, $t0

    # i++
    addi $t0, $t0, 1

    # Ulang
    j    loop

selesai:
    # Tampilkan hasil
    li   $v0, 4
    la   $a0, pesanJumlah
    syscall

    li   $v0, 1
    move $a0, $t2
    syscall

    li   $v0, 10
    syscall