#!/bin/bash
# =====================================================
# TUGAS 8      : Sistem Otomatisasi Administrasi Linux
# MK           : Sistem Operasi
# Nama         : Satrio Nurcahya
# NIM          : 1303180078
# Kelas        : IT-42-01
# File         : admin_lab.sh
# Run          : ./admin_lab.sh [info|disk|hitung|menu|laporan]
# =====================================================

# =====================================================
# 1. DEKLARASI VARIABEL GLOBAL
# =====================================================
NAMA_ADMIN="Satrio Nurcahya"
NAMA_KOMPUTER=$(hostname)
DIREKTORI_KERJA=$(pwd)
BATAS_DISK=80
LOG_FILE="admin_lab.log"
REPORT_FILE="laporan_lab.txt"

# =====================================================
# 2. FUNGSI UTILITAS
# =====================================================

# Fungsi untuk mencatat log
catat_log() {
    local pesan="$1"
    local waktu=$(date "+%Y-%m-%d %H:%M:%S")
    if ! echo "[$waktu] $pesan" >> "$LOG_FILE"; then
        echo "ERROR: Gagal menulis ke file log ($LOG_FILE)"
    fi
}

# Fungsi untuk menampilkan petunjuk penggunaan
tampilkan_petunjuk() {
    echo "====================================================="
    echo "  PENGGUNAAN: $0 [PERINTAH] [ARGUMEN]"
    echo "====================================================="
    echo "  info              : Menampilkan informasi sistem"
    echo "  disk              : Memeriksa penggunaan disk"
    echo "  hitung <a> <b>    : Kalkulator (tambah, kurang, kali, bagi)"
    echo "  laporan           : Membuat laporan ke $REPORT_FILE"
    echo "  menu              : Menampilkan menu interaktif"
    echo "====================================================="
}

# =====================================================
# 3. FUNGSI UTAMA
# =====================================================

# Menampilkan informasi sistem
tampilkan_info() {
    echo "====================================================="
    echo "  INFORMASI SISTEM"
    echo "====================================================="
    echo "Nama Administrator : $NAMA_ADMIN"
    echo "Nama Host/Komputer : $NAMA_KOMPUTER"
    echo "Pengguna Aktif     : $(whoami)"
    echo "Direktori Kerja    : $DIREKTORI_KERJA"
    echo "Waktu Pemeriksaan  : $(date)"
    echo "Sistem Operasi     : $(uname -srm)"
    
    echo -e "\nMemeriksa direktori penting:"
    # Perulangan for untuk mengecek direktori
    for dir in "/home" "/etc" "/var" "/tmp"; do
        if [ -d "$dir" ]; then
            echo "  [OK] Direktori $dir tersedia"
        else
            echo "  [ERROR] Direktori $dir tidak ditemukan"
        fi
    done
    echo "====================================================="
    
    catat_log "INFO: Menampilkan informasi sistem."
}

# Memeriksa penggunaan disk
cek_disk() {
    echo "====================================================="
    echo "  PEMERIKSAAN PENGGUNAAN DISK"
    echo "====================================================="
    echo "Batas Peringatan: $BATAS_DISK%"
    
    # Ambil persentase penggunaan disk root (/)
    # df / | tail -1 | awk '{print $5}' | tr -d '%'
    local penggunaan=$(df / | tail -1 | awk '{print $5}' | tr -d '%')
    
    if ! [[ "$penggunaan" =~ ^[0-9]+$ ]]; then
        echo "ERROR: Gagal membaca penggunaan disk."
        catat_log "ERROR: Gagal membaca penggunaan disk."
        return 1
    fi
    
    echo "Penggunaan Disk Root (/): $penggunaan%"
    
    # Percabangan if-elif-else
    if [ "$penggunaan" -ge 90 ]; then
        echo "STATUS: KRITIS! Segera kosongkan ruang disk."
        catat_log "PERINGATAN: Penggunaan disk kritis ($penggunaan%)."
    elif [ "$penggunaan" -ge "$BATAS_DISK" ]; then
        echo "STATUS: PERINGATAN (Melewati batas $BATAS_DISK%)"
        catat_log "PERINGATAN: Penggunaan disk melewati batas ($penggunaan%)."
    else
        echo "STATUS: NORMAL"
        catat_log "INFO: Penggunaan disk normal ($penggunaan%)."
    fi
    echo "====================================================="
}

# Kalkulator
hitung_angka() {
    local a=$1
    local b=$2
    
    echo "====================================================="
    echo "  KALKULATOR"
    echo "====================================================="
    
    # Validasi input harus angka
    if ! [[ "$a" =~ ^-?[0-9]+$ ]] || ! [[ "$b" =~ ^-?[0-9]+$ ]]; then
        echo "ERROR: Input harus berupa bilangan bulat!"
        catat_log "ERROR: Input kalkulator tidak valid ($a, $b)."
        return 1
    fi
    
    echo "Angka Pertama : $a"
    echo "Angka Kedua   : $b"
    echo "-----------------------------------------------------"
    echo "Penjumlahan   : $((a + b))"
    echo "Pengurangan   : $((a - b))"
    echo "Perkalian     : $((a * b))"
    
    # Penanganan pembagian dengan nol
    if [ "$b" -eq 0 ]; then
        echo "Pembagian     : ERROR (Tidak boleh dibagi nol)"
    else
        echo "Pembagian     : $((a / b))"
    fi
    echo "====================================================="
    
    catat_log "INFO: Melakukan kalkulasi ($a dan $b)."
}

# Membuat laporan
buat_laporan() {
    echo "Membuat laporan ke file $REPORT_FILE..."
    
    {
        echo "====================================================="
        echo "  LAPORAN ADMINISTRASI LABORATORIUM"
        echo "====================================================="
        echo "Dibuat oleh : $NAMA_ADMIN"
        echo "Waktu       : $(date)"
        echo "-----------------------------------------------------"
        echo "INFORMASI SISTEM:"
        echo "Hostname    : $NAMA_KOMPUTER"
        echo "OS          : $(uname -srm)"
        echo "Working Dir : $DIREKTORI_KERJA"
        echo "-----------------------------------------------------"
        echo "PENGGUNAAN DISK:"
        df -h / | tail -1
        echo "-----------------------------------------------------"
        echo "STATUS FILE LOG:"
        if [ -f "$LOG_FILE" ]; then
            echo "File log tersedia ($(wc -l < "$LOG_FILE") baris)."
        else
            echo "File log belum dibuat."
        fi
        echo "====================================================="
    } > "$REPORT_FILE"
    
    if [ $? -eq 0 ]; then
        echo "Laporan berhasil dibuat: $REPORT_FILE"
        catat_log "INFO: Membuat laporan sistem."
    else
        echo "ERROR: Gagal membuat laporan."
        catat_log "ERROR: Gagal membuat laporan."
    fi
}

# Menu Interaktif
tampilkan_menu() {
    local pilihan
    local a, b
    
    # Perulangan while sampai user pilih keluar
    while true; do
        echo ""
        echo "===== ADMINISTRASI LABORATORIUM ====="
        echo "1. Informasi Sistem"
        echo "2. Pemeriksaan Disk"
        echo "3. Kalkulator"
        echo "4. Buat Laporan"
        echo "0. Keluar"
        echo "====================================="
        read -p "Pilih menu: " pilihan
        
        case "$pilihan" in
            1)
                tampilkan_info
                ;;
            2)
                cek_disk
                ;;
            3)
                echo "Masukkan angka pertama: "
                read a
                echo "Masukkan angka kedua: "
                read b
                hitung_angka "$a" "$b"
                ;;
            4)
                buat_laporan
                ;;
            0)
                echo "Terima kasih! Keluar dari menu."
                catat_log "INFO: Keluar dari menu interaktif."
                break
                ;;
            *)
                echo "Pilihan tidak valid! Silakan coba lagi."
                ;;
        esac
    done
}

# =====================================================
# 4. PEMROSESAN ARGUMEN COMMAND-LINE
# =====================================================

# Cek jika tidak ada argumen
if [ $# -eq 0 ]; then
    echo "Tidak ada argumen yang diberikan. Menampilkan petunjuk..."
    tampilkan_petunjuk
    exit 1
fi

case "$1" in
    "info")
        tampilkan_info
        ;;
    "disk")
        cek_disk
        ;;
    "hitung")
        if [ $# -ne 3 ]; then
            echo "ERROR: Format perintah 'hitung' adalah: $0 hitung <angka1> <angka2>"
            exit 1
        fi
        hitung_angka "$2" "$3"
        ;;
    "laporan")
        buat_laporan
        ;;
    "menu")
        tampilkan_menu
        ;;
    *)
        echo "ERROR: Perintah '$1' tidak dikenali!"
        tampilkan_petunjuk
        exit 1
        ;;
esac

exit 0