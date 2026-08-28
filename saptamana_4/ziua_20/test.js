async function cautaUtilizator(){
    try{
        const raspuns = await fetch('https://jsonplaceholder.typicode.com/users/');
        const date = await raspuns.json();

        console.log("Date de la API: ");
        console.log("Nume:", date.name);
        console.log("Email:", date.email);

    }catch (eroare){
        console.error("eroare", eroare);
        
    }
}
cautaUtilizator();