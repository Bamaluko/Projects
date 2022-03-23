<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html" encoding="UTF-8" />
	<xsl:template match="/">
        <xsl:apply-templates select="/osoby/grupaStudentow/student[3]"/>
    </xsl:template>
	<xsl:template match="/osoby/grupaStudentow/student[3]">
		<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="pl" lang="pl">

			<head>
				<center>
					<h1>ZADANIE_6</h1>
				</center>
			</head>
			
			<body>
				
				<h1>ZADANIE_6_1</h1>
				
				<h3>
					Nazwisko biezacego elementu
					<xsl:value-of select="nazwisko"/>
				</h3>
				
				<h3>
					Element bieżący student wraz z podelementami
					<xsl:value-of select="."/>
				</h3>
				
				<h3>
					Element o nazwie grupaPracownikow
					<xsl:value-of select="../../grupaPracownikow"/>
				</h3>
				<h3>
					Punkty studenta o imieniu Stefania
					<xsl:value-of select="../student[imie = 'Stefania']/zdobytePunkty"/>
				</h3>
				
				<h3>
					NrAlbumu i wiek bieżącego elementu student
					<xsl:value-of select="nrAlbumu"/>
					<xsl:value-of select="wiek"/>
				</h3>
				
				<h3>
					Wiek studenta o imieniu Aleksandra
					<xsl:value-of select="../student[imie = 'Aleksandra']/wiek"/>
				</h3>
				
				<h3>
					Numery wszystkich pracowników
					<xsl:for-each select="../../grupaPracownikow/pracownik/nr_prac">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>
				
				<h3>
					Płeć studentów Aleksandra i Teofil oraz wszystkich pracowników
					<xsl:value-of select="../student[imie = 'Aleksandra']/@plec"/>
					<xsl:value-of select="../student[imie = 'Teofil']/@plec"/>
					<xsl:for-each select="../../grupaPracownikow/pracownik">
						<xsl:value-of select="@plec"/>
					</xsl:for-each>

				</h3>

				
				
				
				<h1>ZADANIE_6_2</h1>

				<h3>
					Elementy student o wieku powyżej 21 lat
					<xsl:for-each select="../student[wiek > 21]">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>

				<h3>
					Wszystkie elementy student, które mają atrybut "plec" o wartości "k"
					<xsl:for-each select="../student[@plec = 'k']">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>

				<h3>
					Wszystkich pracowników mężczyzn
					<xsl:for-each select="../../grupaPracownikow/pracownik[@plec = 'm']">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>

				<h3>
					Wszystkich pracowników, których numer pracownika jest większy od 40000
					<xsl:for-each select="../../grupaPracownikow/pracownik[nr_prac > 40000]">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>



				<h1>ZADANIE_6_3</h1>
				
				<h3>
					Drugie wystąpienie elementu student
					<xsl:value-of select="../student[position()=2]"/>
				</h3>

				<h3>
					Trzecie i kolejne wystąpienie student
					<xsl:for-each select="../student[position()>=2]">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>

				<h3>
					Wszystkich poza drugim wystąpieniem elementu student
					<xsl:for-each select="../student[position()!=2]">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>

				<h3>
					Wszystkie elementy, które są drugim dzieckiem swojego ojca
					<xsl:for-each select="//*[position()=2]">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>

				<h3>
					Podostatniego pracownika i studenta
					<xsl:value-of select="../student[last()-1]"/>
					<xsl:value-of select="../../grupaPracownikow/pracownik[last()-1]"/>
				</h3>

				<h3>
					Od drugiego włącznie pracownika
					<xsl:for-each select="../../grupaPracownikow/pracownik[position()>=2]">
						<xsl:value-of select="."/>
					</xsl:for-each>
				</h3>
				
				<h1>ZADANIE_6_4</h1>
				
				<h3>
					Wszystkie wartości wiek korzystając z funkcji text()
					<xsl:for-each select="../student">
						<xsl:value-of select="wiek[text()]"/>
					</xsl:for-each>
				</h3>

				<h3>
					Sumę wartości wiek wszystkich pracowników
					<xsl:value-of select="sum(../student/wiek)"/>
				</h3>

				<h3>
					Średnią wieku mężczyzn
					<xsl:value-of select="sum(../student[@plec = 'm']/wiek) div count(../student[@plec = 'm'])"/>
				</h3>

				<h3>
					Łańcuch znaków imie oraz nazwisko rozdzielone spacją, np. Teofil Różyc
					<xsl:value-of select="normalize-space(concat(imie, ' ', nazwisko))"/>
				</h3>

				<h3>
					Najmłodszego i najstarszego studenta i pracownika
                    <xsl:for-each select="../student">
						<xsl:sort select="wiek" data-type="number" order="ascending" />
						<xsl:if test="position() = 1">
							Najmlodszy student:
							<xsl:value-of select="." />
						</xsl:if>
						<xsl:if test="position() = last()">
							Najstarszy student:
							<xsl:value-of select="." />
						</xsl:if>
					</xsl:for-each>
                    <xsl:for-each select="../../grupaPracownikow/pracownik">
						<xsl:sort select="wiek" data-type="number" order="ascending" />
						<xsl:if test="position() = 1">
							Najmlodszy pracownik:
							<xsl:value-of select="." />
						</xsl:if>
						<xsl:if test="position() = last()">
							Najstarszy pracownik:
							<xsl:value-of select="." />
						</xsl:if>
					</xsl:for-each>
				</h3>

				<h3>
					Liczbę kobiet i mężczyzn (zarówno studentów, jak i pracowników)
					Liczba kobiet:
					<xsl:value-of select="count(../student[@plec = 'k']) + count(../../grupaPracownikow/pracownik[@plec = 'k'])"/>
					Liczba mezczyzn:
					<xsl:value-of select="count(../student[@plec = 'm']) + count(../../grupaPracownikow/pracownik[@plec = 'm'])"/>
						
				</h3>
				
				<h3>
					Liczbę kobiet i mężczyzn dla poszczególnych grup (studentów i osobno dla pracowników)
					Liczba kobiet (studenci):
					<xsl:value-of select="count(../student[@plec = 'k'] )"/>
					Liczba mezczyzn (studenci):
					<xsl:value-of select="count(../student[@plec = 'm'] )"/>
					Liczba kobiet (pracownicy):
					<xsl:value-of select="count(../../grupaPracownikow/pracownik[@plec = 'k'] )"/>
					Liczba mezczyzn (pracownicy):
					<xsl:value-of select="count(../../grupaPracownikow/pracownik[@plec = 'm'] )"/>						
				</h3>
				
				<h3>
					Największą i najmniejszą liczbę zdobytych punktów przez studentów
                    <xsl:for-each select="../student">
						<xsl:sort select="zdobytePunkty" data-type="number" order="ascending" />
						<xsl:if test="position() = 1">
							Min:
							<xsl:value-of select="." />
						</xsl:if>
						<xsl:if test="position() = last()">
							Max:
							<xsl:value-of select="." />
						</xsl:if>
					</xsl:for-each>
				</h3>
				
				<h3>
					Średnią liczbę zdobytych punktów przez studentów
					<xsl:value-of select="sum(../student/zdobytePunkty) div count(../student)"/>
				</h3>
				
				<h3>
					Liczbę studentów, którzy zdali, czyli zyskali powyżej 50 punktów
					<xsl:value-of select="count(../student[zdobytePunkty>50])"/>
				</h3>
				
			</body>
		
		</html>
		
	</xsl:template>
	
</xsl:stylesheet>
