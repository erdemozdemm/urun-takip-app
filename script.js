// Ürün verilerini saklamak için dizi
let urunler = [];

// DOM elementleri
const urunForm = document.getElementById('urunForm');
const urunAd = document.getElementById('urunAd');
const urunFiyat = document.getElementById('urunFiyat');
const urunAdet = document.getElementById('urunAdet');
const urunListesi = document.getElementById('urunListesi');
const toplamDeger = document.getElementById('toplamDeger');
const bosMesaj = document.getElementById('bosMesaj');
const editModal = document.getElementById('editModal');
const editForm = document.getElementById('editForm');
const editIndex = document.getElementById('editIndex');
const editAd = document.getElementById('editAd');
const editFiyat = document.getElementById('editFiyat');
const editAdet = document.getElementById('editAdet');
const closeModal = document.querySelector('.close');

// Sayfa yüklendiğinde localStorage'dan verileri yükle
document.addEventListener('DOMContentLoaded', function() {
    urunleriYukle();
    urunleriGoster();
});

// Ürün ekleme formu
urunForm.addEventListener('submit', function(e) {
    e.preventDefault();
    
    const yeniUrun = {
        ad: urunAd.value.trim(),
        fiyat: parseFloat(urunFiyat.value),
        adet: parseInt(urunAdet.value)
    };
    
    urunler.push(yeniUrun);
    urunleriKaydet();
    urunleriGoster();
    
    // Formu temizle
    urunForm.reset();
    urunAd.focus();
});

// Ürün düzenleme formu
editForm.addEventListener('submit', function(e) {
    e.preventDefault();
    
    const index = parseInt(editIndex.value);
    
    urunler[index] = {
        ad: editAd.value.trim(),
        fiyat: parseFloat(editFiyat.value),
        adet: parseInt(editAdet.value)
    };
    
    urunleriKaydet();
    urunleriGoster();
    modalKapat();
});

// Modal kapatma
closeModal.addEventListener('click', modalKapat);
window.addEventListener('click', function(e) {
    if (e.target === editModal) {
        modalKapat();
    }
});

// Ürünleri göster
function urunleriGoster() {
    urunListesi.innerHTML = '';
    
    if (urunler.length === 0) {
        bosMesaj.style.display = 'block';
        toplamDeger.textContent = '0.00';
        return;
    }
    
    bosMesaj.style.display = 'none';
    
    urunler.forEach(function(urun, index) {
        const toplam = urun.fiyat * urun.adet;
        const satir = document.createElement('tr');
        
        satir.innerHTML = `
            <td>${index + 1}</td>
            <td>${urun.ad}</td>
            <td>${urun.fiyat.toFixed(2)} TL</td>
            <td>${urun.adet}</td>
            <td>${toplam.toFixed(2)} TL</td>
            <td>
                <button class="btn-edit" onclick="urunDuzenle(${index})">Düzenle</button>
                <button class="btn-delete" onclick="urunSil(${index})">Sil</button>
            </td>
        `;
        
        urunListesi.appendChild(satir);
    });
    
    toplamDegeriHesapla();
}

// Toplam stok değerini hesapla
function toplamDegeriHesapla() {
    let genelToplam = 0;
    
    urunler.forEach(function(urun) {
        genelToplam += urun.fiyat * urun.adet;
    });
    
    toplamDeger.textContent = genelToplam.toFixed(2);
}

// Ürün sil
function urunSil(index) {
    if (confirm('Bu ürünü silmek istediğinizden emin misiniz?')) {
        urunler.splice(index, 1);
        urunleriKaydet();
        urunleriGoster();
    }
}

// Ürün düzenle
function urunDuzenle(index) {
    const urun = urunler[index];
    
    editIndex.value = index;
    editAd.value = urun.ad;
    editFiyat.value = urun.fiyat;
    editAdet.value = urun.adet;
    
    editModal.style.display = 'block';
}

// Modal kapat
function modalKapat() {
    editModal.style.display = 'none';
}

// Verileri localStorage'a kaydet
function urunleriKaydet() {
    localStorage.setItem('urunler', JSON.stringify(urunler));
}

// Verileri localStorage'dan yükle
function urunleriYukle() {
    const kayitliUrunler = localStorage.getItem('urunler');
    if (kayitliUrunler) {
        urunler = JSON.parse(kayitliUrunler);
    }
}

// Klavye kısayolları
document.addEventListener('keydown', function(e) {
    // ESC tuşu modalı kapatır
    if (e.key === 'Escape' && editModal.style.display === 'block') {
        modalKapat();
    }
});
