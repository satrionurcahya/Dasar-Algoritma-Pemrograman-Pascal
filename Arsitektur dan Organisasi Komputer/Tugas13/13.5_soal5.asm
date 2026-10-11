# =====================================================
# TUGAS 13.5 - SOAL 5
# hasil = n × n, dengan n = 12
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanHasil : .asciiz "Hasil kuadrat = "

.text
.globl main

main:
    li $t0, 12          # n = 12

    # Hitung n * n
    mult $t0, $t0
    mflo $s0            # $s0 = 12 * 12 = 144

    # Tampilkan
    li $v0, 4
    la $a0, pesanHasil
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall